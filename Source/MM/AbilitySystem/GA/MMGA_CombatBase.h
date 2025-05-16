// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MMGA_CombatBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MM_API UMMGA_CombatBase : public UGameplayAbility
{
	GENERATED_BODY()
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;
	
	const AActor* GetTargetFromComponent();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float SearchRadius = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float AttackRange = 150.f;

};
