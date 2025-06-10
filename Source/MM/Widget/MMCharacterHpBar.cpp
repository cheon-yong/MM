// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MMCharacterHpBar.h"
#include "AbilitySystem/AttributeSet/MMAttributeSet.h"
#include "Components/ProgressBar.h"

void UMMCharacterHpBar::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		const UMMAttributeSet* CurrentAttributeSet = ASC->GetSet<UMMAttributeSet>();
		if (CurrentAttributeSet)
		{
			CurrentAttributeSet->OnHealthChanged.AddUObject(this, &ThisClass::OnHealthChanged);
			CurrentAttributeSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::OnMaxHealthChanged);

			CurrentHealth = CurrentAttributeSet->GetHealth();
			CurrentMaxHealth = CurrentAttributeSet->GetMaxHealth();

			if (CurrentMaxHealth > 0.0f)
			{
				UpdateHpBar();
			}
		}
	}
}

void UMMCharacterHpBar::OnHealthChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	CurrentHealth = NewValue;
	UpdateHpBar();
}

void UMMCharacterHpBar::OnMaxHealthChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	CurrentMaxHealth = NewValue;
	UpdateHpBar();
}

UE_DISABLE_OPTIMIZATION
void UMMCharacterHpBar::UpdateHpBar()
{
	if (PbHpBar)
	{
		float Percent = CurrentHealth / CurrentMaxHealth;
		PbHpBar->SetPercent(Percent);
	}
}
UE_ENABLE_OPTIMIZATION