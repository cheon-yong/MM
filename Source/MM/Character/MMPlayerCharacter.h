// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/MMCharacter.h"
#include "Delegates/IDelegateInstance.h"
#include "AbilitySystemInterface.h"
#include "MMPlayerCharacter.generated.h"

class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class MM_API AMMPlayerCharacter : public AMMCharacter
{
	GENERATED_BODY()

public:
	AMMPlayerCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	void Zoom(float Time, float TargetFOV, UCurveFloat* Curve);

	UFUNCTION(BlueprintCallable)
	void SetTimeDilation(float InTargetDilation, float InTime);

	UFUNCTION(BlueprintCallable)
	void ActivatePostProcessing(float Time, int Index, UCurveFloat* Curve);

public:
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<UGameplayAbility>> StartInputAbilities;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

#pragma region TimeDilation

	FTSTicker::FDelegateHandle DilationHandle;

	UPROPERTY(Transient)
	float OriginDilation = 0.f;

	UPROPERTY(Transient)
	float TagetDilation = 0.f;
#pragma endregion

#pragma region Zoom Variable
	UPROPERTY(Transient)
	FTimerHandle ZoomHandle;

	UPROPERTY(Transient)
	float StartFOV = 0.f;

	UPROPERTY(Transient)
	float EndFOV = 0.f;

	UPROPERTY(Transient)
	float ZoomDuration = 0.f;

	UPROPERTY(Transient)
	float ZoomElapseTime = 0.f;

	UPROPERTY(Transient)
	TObjectPtr<UCurveFloat> ZoomCurve = nullptr;

#pragma endregion

#pragma region Post Process
	UPROPERTY(Transient)
	FTimerHandle PPHandle;

	UPROPERTY(Transient)
	int32 PP_Index = INDEX_NONE;

	UPROPERTY(Transient)
	float PP_ActiveDuration = 0.f;

	UPROPERTY(Transient)
	float PP_ElapseTime = 0.f;

	UPROPERTY(Transient)
	TObjectPtr<UCurveFloat> PP_Curve = nullptr;
#pragma endregion
};
