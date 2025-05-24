// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Shakes/SimpleCameraShakePattern.h"
#include "Shakes/WaveOscillatorCameraShakePattern.h"

#include "CurveCameraShakePattern.generated.h"

class UCurveFloat;

/**
 * 
 */
UCLASS()
class UCurveCameraShakePattern : public USimpleCameraShakePattern
{
	GENERATED_BODY()
	
	
public:
	UCurveCameraShakePattern(const FObjectInitializer& ObjInit);

protected:

	// UCameraShakePattern interface
	virtual void StartShakePatternImpl(const FCameraShakePatternStartParams& Params) override;
	virtual void UpdateShakePatternImpl(const FCameraShakePatternUpdateParams& Params, FCameraShakePatternUpdateResult& OutResult) override;
	virtual void ScrubShakePatternImpl(const FCameraShakePatternScrubParams& Params, FCameraShakePatternUpdateResult& OutResult) override;

	void UpdateOscillators(float DeltaTime, FCameraShakePatternUpdateResult& OutResult);
	void UpdateCurveNoise(float DeltaTime, FCameraShakePatternUpdateResult& OutResult);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	UCurveFloat* AmplitudeCurve;

	UPROPERTY(Transient)
	float CurveMinTime = 0.f;
	
	UPROPERTY(Transient)
	float CurveMaxTime = 0.f;

	/** Amplitude multiplier for all location oscillation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
	float LocationAmplitudeMultiplier = 1.f;

	/** Frequency multiplier for all location oscillation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
	float LocationFrequencyMultiplier = 1.f;

	/** Oscillation in the X axis. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
	FWaveOscillator X;

	/** Oscillation in the Y axis. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
	FWaveOscillator Y;

	/** Oscillation in the Z axis. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Location)
	FWaveOscillator Z;

	/** Amplitude multiplier for all rotation oscillation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float RotationAmplitudeMultiplier = 1.f;

	/** Frequency multiplier for all rotation oscillation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	float RotationFrequencyMultiplier = 1.f;

	/** Pitch oscillation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	FWaveOscillator Pitch;

	/** Yaw oscillation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	FWaveOscillator Yaw;

	/** Roll oscillation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
	FWaveOscillator Roll;

	/** FOV oscillation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FOV)
	FWaveOscillator FOV;

private:

	float ElapsedTime = 0.f;

	/** Initial sinusoidal offset for location oscillation. */
	FVector3f InitialLocationOffset;
	/** Current sinusoidal offset for location oscillation. */
	FVector3f CurrentLocationOffset;

	/** Initial sinusoidal offset for rotation oscillation. */
	FVector3f InitialRotationOffset;
	/** Current sinusoidal offset for rotation oscillation. */
	FVector3f CurrentRotationOffset;

	/** Initial sinusoidal offset for FOV oscillation */
	float InitialFOVOffset;
	/** Current sinusoidal offset for FOV oscillation */
	float CurrentFOVOffset;
};
