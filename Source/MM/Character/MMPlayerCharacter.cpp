// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MMPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MMPlayerState.h"

AMMPlayerCharacter::AMMPlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AMMPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AMMPlayerState* MMPS = GetPlayerState<AMMPlayerState>();

	if (MMPS)
	{
		ASC = MMPS->GetAbilitySystemComponent();
		ASC->InitAbilityActorInfo(MMPS, this);

		for (const auto& StartInputAbility : StartInputAbilities)
		{
			FGameplayAbilitySpec StartSpec(StartInputAbility.Value);
			StartSpec.InputID = StartInputAbility.Key;
			ASC->GiveAbility(StartSpec);
		}

		AttributeSet = MMPS->GetAttributeSet();
	}

}

void AMMPlayerCharacter::Zoom(float ZoomTime, float TargetFOV)
{
	StartFOV = FollowCamera->FieldOfView;
	EndFOV = TargetFOV;
	ZoomDuration = FMath::Max(0.f, ZoomTime);

	FTimerDelegate TimerDelegate;
	ZoomElapseTime = 0.f;


	TimerDelegate = FTimerDelegate::CreateLambda([&]() mutable {
		ZoomElapseTime += GetWorld()->GetDeltaSeconds();

		float Alpha = FMath::Clamp(ZoomElapseTime / ZoomDuration, 0.f, 1.f);
		float CurrentFOV = FMath::Lerp(StartFOV, EndFOV, Alpha);
		FollowCamera->FieldOfView = CurrentFOV;
	});

	GetWorldTimerManager().SetTimer(
		ZoomHandle,
		TimerDelegate,
		GetWorld()->GetDeltaSeconds(),
		true,
		0.f
	);
}
