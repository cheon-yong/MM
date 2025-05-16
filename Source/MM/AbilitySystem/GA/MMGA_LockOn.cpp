// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GA/MMGA_LockOn.h"

UMMGA_LockOn::UMMGA_LockOn()
{
}

void UMMGA_LockOn::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

AActor* UMMGA_LockOn::FindClosestTarget() const
{
	return nullptr;
}
