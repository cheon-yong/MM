// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "MMGA_CombatBase.generated.h"

class UMMAT_MoveToTarget;
class UMMAT_FindTarget;
class UAbilityTask_PlayMontageAndWait;
class UMMAT_HitTrace;
class UAbilitySystemComponent;
class UGameplayEffect;

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

	void HitCheck();

protected:

	UFUNCTION()
	void OnTargetAcquired(AActor* Target);

	UFUNCTION(BlueprintNativeEvent)
	void OnTargetInRange(AActor* Target);

	UFUNCTION(BlueprintNativeEvent)
	void OnAttackMontageFinished();

	UFUNCTION()
	void OnHitCheck(const TArray<FHitResult>& HitResults);

	void ApplyDamageToTarget(UAbilitySystemComponent* TargetASC);


public:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SearchRadius = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackRange = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UGameplayEffect> AttackDamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FGameplayTag TargetTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat", meta = (Categories = "GameplayCue"))
	FGameplayTag HitCueTag;

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
	TObjectPtr<UMMAT_HitTrace> HitTask;

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
};
