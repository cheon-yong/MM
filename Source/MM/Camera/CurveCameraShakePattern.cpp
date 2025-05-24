// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CurveCameraShakePattern.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(CurveCameraShakePattern)

UCurveCameraShakePattern::UCurveCameraShakePattern(const FObjectInitializer& ObjInit)
	: Super(ObjInit)
{
	// Default to only location shaking.
	RotationAmplitudeMultiplier = 0.f;
	FOV.Amplitude = 0.f;
}

void UCurveCameraShakePattern::StartShakePatternImpl(const FCameraShakePatternStartParams& Params)
{
	Super::StartShakePatternImpl(Params);

	if (!Params.bIsRestarting)
	{
		X.Initialize(InitialLocationOffset.X);
		Y.Initialize(InitialLocationOffset.Y);
		Z.Initialize(InitialLocationOffset.Z);

		CurrentLocationOffset = InitialLocationOffset;

		Pitch.Initialize(InitialRotationOffset.X);
		Yaw.Initialize(InitialRotationOffset.Y);
		Roll.Initialize(InitialRotationOffset.Z);

		CurrentRotationOffset = InitialRotationOffset;

		FOV.Initialize(InitialFOVOffset);

		CurrentFOVOffset = InitialFOVOffset;
	}

	ElapsedTime = 0.f;
	if (nullptr == AmplitudeCurve)
		return;

	AmplitudeCurve->GetTimeRange(CurveMinTime, CurveMaxTime);
}

void UCurveCameraShakePattern::UpdateShakePatternImpl(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult)
{
	ElapsedTime += Params.DeltaTime;
	UpdateOscillators(Params.DeltaTime, OutResult);

	const float BlendWeight = State.Update(Params.DeltaTime);
	OutResult.ApplyScale(BlendWeight);
}

void UCurveCameraShakePattern::ScrubShakePatternImpl(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult)
{
	// Scrubbing is like going back to our initial state and updating directly to the scrub time.
	CurrentLocationOffset = InitialLocationOffset;
	CurrentRotationOffset = InitialRotationOffset;
	CurrentFOVOffset = InitialFOVOffset;

	UpdateOscillators(Params.AbsoluteTime, OutResult);

	const float BlendWeight = State.Scrub(Params.AbsoluteTime);
	OutResult.ApplyScale(BlendWeight);
}


void UCurveCameraShakePattern::UpdateOscillators(float DeltaTime, FCameraShakePatternUpdateResult& OutResult)
{
	OutResult.Location.X = X.Update(DeltaTime, LocationAmplitudeMultiplier, LocationFrequencyMultiplier, CurrentLocationOffset.X);
	OutResult.Location.Y = Y.Update(DeltaTime, LocationAmplitudeMultiplier, LocationFrequencyMultiplier, CurrentLocationOffset.Y);
	OutResult.Location.Z = Z.Update(DeltaTime, LocationAmplitudeMultiplier, LocationFrequencyMultiplier, CurrentLocationOffset.Z);

	OutResult.Rotation.Pitch = Pitch.Update(DeltaTime, RotationAmplitudeMultiplier, RotationFrequencyMultiplier, CurrentRotationOffset.X);
	OutResult.Rotation.Yaw = Yaw.Update(DeltaTime, RotationAmplitudeMultiplier, RotationFrequencyMultiplier, CurrentRotationOffset.Y);
	OutResult.Rotation.Roll = Roll.Update(DeltaTime, RotationAmplitudeMultiplier, RotationFrequencyMultiplier, CurrentRotationOffset.Z);

	OutResult.FOV = FOV.Update(DeltaTime, 1.f, 1.f, CurrentFOVOffset);

	UpdateCurveNoise(DeltaTime, OutResult);
}

void UCurveCameraShakePattern::UpdateCurveNoise(float DeltaTime, FCameraShakePatternUpdateResult& OutResult)
{
	if (AmplitudeCurve == nullptr)
		return;

	float NormalizedTime = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f);

	float CurveEvalTime = FMath::Lerp(CurveMinTime, CurveMaxTime, NormalizedTime);

	float CurveScale = AmplitudeCurve->GetFloatValue(CurveEvalTime);

	OutResult.Location.X *= CurveScale;
	OutResult.Location.Y *= CurveScale;
	OutResult.Location.Z *= CurveScale;

	OutResult.Rotation.Pitch *= CurveScale;
	OutResult.Rotation.Yaw *= CurveScale;
	OutResult.Rotation.Roll *= CurveScale;

	OutResult.FOV *= CurveScale;
}
