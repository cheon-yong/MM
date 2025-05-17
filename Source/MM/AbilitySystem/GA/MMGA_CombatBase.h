// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "MMGA_CombatBase.generated.h"

class UMMAT_MoveToTarget;
class UMMAT_FindTarget;
class UAbilityTask_PlayMontageAndWait;

/**
 * 
 */
UCLASS(Abstract)
class MM_API UMMGA_CombatBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	AActor* GetTargetFromComponent() const;

protected:

	UFUNCTION()
	void OnTargetAcquired(AActor* Target);

	UFUNCTION(BlueprintNativeEvent)
	void OnTargetInRange(AActor* Target);

	UFUNCTION(BlueprintNativeEvent)
	void OnAttackMontageFinished();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SearchRadius = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackRange = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FGameplayTag TargetTag;
		
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY()
	TObjectPtr<UMMAT_FindTarget> TargetTask;

	UPROPERTY()
	TObjectPtr<UMMAT_MoveToTarget> MoveTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_PlayMontageAndWait> MontageTask;

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
};
