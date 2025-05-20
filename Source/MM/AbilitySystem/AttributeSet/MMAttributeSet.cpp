// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSet/MMAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UMMAttributeSet::UMMAttributeSet() :
	MaxAttackRange(300.0f),
	AttackRange(100.0f),
	MaxAttackRadius(150.0f),
	AttackRadius(50.f),
	MaxAttackSpeed(2.0f),
	AttackSpeed(1.0f),
	MaxAttackRate(100.0f),
	AttackRate(30.0f),
	MaxHealth(100.0f),
	MaxStamina(100.f),
	MaxBreakGauge(100.f),
	Damage(0.0f)
{
	InitHealth(GetMaxHealth());
	InitStamina(GetMaxStamina());
	InitBreakGauge(GetMaxBreakGauge());
}

void UMMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMMAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UMMAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UMMAttributeSet, BreakGauge, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMAttributeSet, MaxBreakGauge, COND_None, REPNOTIFY_Always);
}

void UMMAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetDamageAttribute())
	{
		NewValue = NewValue < 0.0f ? 0.0f : NewValue;
	}
}

bool UMMAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Data.EvaluatedData.Magnitude > 0.0f)
		{
			/*if (Data.Target.HasMatchingGameplayTag(ABTAG_CHARACTER_INVINSIBLE))
			{
				Data.EvaluatedData.Magnitude = 0.0f;
				return false;
			}*/
		}
	}

	HealthBeforeAttributeChange = GetHealth();
	MaxHealthBeforeAttributeChange = GetMaxHealth();

	StaminaBeforeAttributeChange = GetStamina();
	MaxStaminaBeforeAttributeChange = GetMaxStamina();

	BreakGaugeBeforeAttributeChange = GetBreakGauge();
	MaxBreakGaugeBeforeAttributeChange = GetMaxBreakGauge();

	return true;
}

void UMMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	float MinimumHealth = 0.0f;

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), MinimumHealth, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumHealth, GetMaxHealth()));
		SetDamage(0.0f);
	}

	if ((GetHealth() <= 0.0f) && !bOutOfHealth)
	{
		//Data.Target.AddLooseGameplayTag(ABTAG_CHARACTER_ISDEAD);
		OnOutOfHealth.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeAttributeChange, GetHealth());
	}

	bOutOfHealth = (GetHealth() <= 0.0f);
}



// Network
void UMMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
}

void UMMAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
}

void UMMAttributeSet::OnRep_BreakGauge(const FGameplayAttributeData& OldValue)
{
}

void UMMAttributeSet::OnRep_MaxBreakGauge(const FGameplayAttributeData& OldValue)
{
}
// End Network