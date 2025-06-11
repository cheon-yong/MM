// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MMCharacterBreakBar.h"
#include "AbilitySystem/AttributeSet/MMAttributeSet.h"
#include "Components/ProgressBar.h"

void UMMCharacterBreakBar::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (ASC)
	{
		const UMMAttributeSet* CurrentAttributeSet = ASC->GetSet<UMMAttributeSet>();
		if (CurrentAttributeSet)
		{
			CurrentAttributeSet->OnBreakGaugeChanged.AddUObject(this, &ThisClass::OnBreakChanged);
			CurrentAttributeSet->OnMaxBreakGaugeChanged.AddUObject(this, &ThisClass::OnMaxBreakChanged);

			CurrentBreak = CurrentAttributeSet->GetBreakGauge();
			CurrentMaxBreak = CurrentAttributeSet->GetMaxBreakGauge();

			if (CurrentMaxBreak > 0.0f)
			{
				UpdateBreakBar();
			}
		}
	}
}

void UMMCharacterBreakBar::OnBreakChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	CurrentBreak = NewValue;
	UpdateBreakBar();
}

void UMMCharacterBreakBar::OnMaxBreakChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	CurrentMaxBreak = NewValue;
	UpdateBreakBar();
}

void UMMCharacterBreakBar::UpdateBreakBar()
{
	if (PbBreakBar)
	{
		float Percent = CurrentBreak / CurrentMaxBreak;
		PbBreakBar->SetPercent(Percent);
	}
}
