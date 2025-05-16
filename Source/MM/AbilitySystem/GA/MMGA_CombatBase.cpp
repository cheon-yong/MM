// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GA/MMGA_CombatBase.h"

#include "Character/AutoCombatComponent.h"

void UMMGA_CombatBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const AActor* TargetActor = GetTargetFromComponent();

	if (nullptr == TargetActor)
	{

	}
}

const AActor* UMMGA_CombatBase::GetTargetFromComponent()
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	if (nullptr == Avatar)
	{
		return nullptr;
	}

	if (UAutoCombatComponent* AutoCombatComp = Avatar->GetComponentByClass<UAutoCombatComponent>())
	{
		return AutoCombatComp->TargetActor;
	}

	return nullptr;
}
