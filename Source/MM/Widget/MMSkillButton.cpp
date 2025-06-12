// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MMSkillButton.h"
#include "AbilitySystemComponent.h"

void UMMSkillButton::BindOnAppliedEffect()
{
	if (ASC)
	{
		ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(this, &ThisClass::OnEffectAdded);
	}
}

void UMMSkillButton::OnEffectAdded(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle Handle)
{
	if (SpecApplied.Def->GetGrantedTags().HasTag(CooldownTag))
	{
		float CoolTimeDuration = SpecApplied.GetDuration();

		SetCoolTime(CoolTimeDuration);
	}
}
