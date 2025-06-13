// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MMNonPlayerCharacter.h"

#include "AI/MMAIController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/MMAttributeSet.h"
#include "Widget/MMWidgetComponent.h"
#include "Widget/MMCharacterHpBar.h"


AMMNonPlayerCharacter::AMMNonPlayerCharacter()
{
}

void AMMNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ASC->InitAbilityActorInfo(this, this);
	ASC->AddLooseGameplayTags(InitTags);

	if (const UMMAttributeSet* CurrentAttributeSet = ASC->GetSet<UMMAttributeSet>())
	{
		CurrentAttributeSet->OnOutOfBreakGauge.AddUObject(this, &ThisClass::OnBreak);
		CurrentAttributeSet->OnOutOfHealth.AddUObject(this, &ThisClass::OnHealthZero);
	}

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		ASC->GiveAbility(StartSpec);
	}
}

void AMMNonPlayerCharacter::OnBreak(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(EffectInstigator))
	{
		UAbilitySystemComponent* InstigatorASC = ASCInterface->GetAbilitySystemComponent();
		if (InstigatorASC)
		{
			FGameplayCueParameters Params;
			Params.Location = GetActorLocation();
			Params.Instigator = EffectInstigator;
			Params.OriginalTag = FGameplayTag::RequestGameplayTag("GameplayCue.Break");

			InstigatorASC->ExecuteGameplayCue(FGameplayTag::RequestGameplayTag("GameplayCue.Break"), Params);
		}
	}
}

void AMMNonPlayerCharacter::OnHealthZero(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	if (AMMAIController* AIController = Cast<AMMAIController>(GetController()))
	{
		AIController->StopAI();
	}
}
