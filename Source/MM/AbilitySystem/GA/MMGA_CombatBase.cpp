// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GA/MMGA_CombatBase.h"

#include "AbilitySystem/AT/MMAT_FindTarget.h"
#include "AbilitySystem/AT/MMAT_MoveToTarget.h"
#include "Character/AutoCombatComponent.h"


void UMMGA_CombatBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	TargetActor = GetTargetFromComponent();

	if (nullptr == TargetActor)
	{
		TargetTask = UMMAT_FindTarget::FindTarget(this, SearchRadius, TargetTag);
		TargetTask->OnTargetFound.AddDynamic(this, &ThisClass::OnTargetAcquired);
		TargetTask->ReadyForActivation();
	}
}

AActor* UMMGA_CombatBase::GetTargetFromComponent() const
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

void UMMGA_CombatBase::OnTargetAcquired(AActor* InTarget)
{
	if (nullptr == InTarget)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	TargetActor = InTarget;
	MoveTask = UMMAT_MoveToTarget::MoveToTarget(this, TargetActor, AttackRange);
	MoveTask->OnArrived.AddDynamic(this, &UMMGA_CombatBase::OnTargetInRange);
	MoveTask->ReadyForActivation();
}

void UMMGA_CombatBase::OnTargetInRange_Implementation(AActor* Target)
{
	UE_LOG(LogTemp, Warning, TEXT("In Range"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
