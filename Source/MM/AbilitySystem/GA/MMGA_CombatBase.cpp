// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GA/MMGA_CombatBase.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameplayEffect.h"
#include "AbilitySystem/AT/MMAT_FindTarget.h"
#include "AbilitySystem/AT/MMAT_MoveToTarget.h"
#include "AbilitySystem/AT/MMAT_HitTrace.h"
#include "Character/AutoCombatComponent.h"
#include "AbilitySystem/AttributeSet/MMAttributeSet.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemGlobals.h>


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

void UMMGA_CombatBase::HitCheck()
{
	HitTask = UMMAT_HitTrace::PerformHitTrace(this, TargetActor, AttackRange);
	HitTask->OnHit.AddDynamic(this, &ThisClass::OnHitCheck);
	HitTask->ReadyForActivation();
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
	MoveTask->OnArrived.AddDynamic(this, &ThisClass::OnTargetInRange);
	MoveTask->ReadyForActivation();
}

void UMMGA_CombatBase::OnHitCheck(const TArray<FHitResult>& HitResults)
{
	for (const FHitResult& HitResult : HitResults)
	{
		
		UAbilitySystemComponent* TargetASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(HitResult.GetActor());
		if (!TargetASC)
		{
			UE_LOG(LogTemp, Error, TEXT("ASC not found!"));
			return;
		}

		ApplyDamageToTarget(TargetASC);


		//FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffect, CurrentLevel);
		//if (EffectSpecHandle.IsValid())
		//{
		//	//EffectSpecHandle.Data->SetSetByCallerMagnitude(ABTAG_DATA_DAMAGE, -SourceAttribute->GetAttackRate());			
		//	ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetDataHandle);

		//	FGameplayEffectContextHandle CueContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(EffectSpecHandle);
		//	CueContextHandle.AddHitResult(HitResult);
		//	FGameplayCueParameters CueParam;
		//	CueParam.EffectContext = CueContextHandle;

		//	TargetASC->ExecuteGameplayCue(HitCueTag, CueParam);
		//}
	}
}

void UMMGA_CombatBase::ApplyDamageToTarget(UAbilitySystemComponent* TargetASC)
{
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
	const UMMAttributeSet* SourceAttribute = SourceASC->GetSet<UMMAttributeSet>();

	if (!AttackDamageEffect) 
		return;

	// 1. EffectContext 생성
	FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(this); // 옵션: 어떤 Ability에서 나왔는지 추적

	// 2. EffectSpecHandle 생성 (레벨 지정 가능)
	FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(AttackDamageEffect, GetAbilityLevel(), EffectContext);

	if (SpecHandle.IsValid())
	{
		// 3. 대상에게 적용
		SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
	}
}

void UMMGA_CombatBase::OnTargetInRange_Implementation(AActor* Target)
{
	if (!AttackMontage || !TargetActor)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		return;
	}

	MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage);

	MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnAttackMontageFinished);
	MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnAttackMontageFinished);
	MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnAttackMontageFinished);
	MontageTask->ReadyForActivation();	
}

void UMMGA_CombatBase::OnAttackMontageFinished_Implementation()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}