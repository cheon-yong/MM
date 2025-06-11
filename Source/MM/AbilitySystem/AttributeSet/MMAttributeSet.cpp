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
	InitBreakGauge(0);
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
	if (Attribute == GetDamageAttribute() || Attribute == GetBreakDamageAttribute())
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

	float MinimumValue = 0.0f;

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), MinimumValue, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() - GetDamage(), MinimumValue, GetMaxHealth()));
		SetDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetBreakDamageAttribute())
	{
		SetBreakGauge(FMath::Clamp(GetBreakGauge() + GetBreakDamage(), MinimumValue, GetMaxBreakGauge()));
		SetBreakDamage(0.0f);
	}

	// If health has actually changed activate callbacks
	if (GetHealth() != HealthBeforeAttributeChange)
	{
		OnHealthChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeAttributeChange, GetHealth());
	}

	if (GetBreakGauge() != BreakGaugeBeforeAttributeChange)
	{
		OnBreakGaugeChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, BreakGaugeBeforeAttributeChange, GetBreakGauge());
	}

	if ((GetHealth() <= 0.0f) && !bOutOfHealth)
	{
		//Data.Target.AddLooseGameplayTag(ABTAG_CHARACTER_ISDEAD);
		OnOutOfHealth.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthBeforeAttributeChange, GetHealth());
	}

	if ((GetBreakGauge() <= 0.0f))
	{
		OnOutOfBreakGauge.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, BreakGaugeBeforeAttributeChange, GetBreakGauge());
	}

	bOutOfHealth = (GetHealth() <= 0.0f);
}



// Network
void UMMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMAttributeSet, Health, OldValue);

	const float CurrentHealth = GetHealth();
	const float EstimatedMagnitude = CurrentHealth - OldValue.GetCurrentValue();

	OnHealthChanged.Broadcast(nullptr, nullptr, nullptr, EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentHealth);

	if (!bOutOfHealth && CurrentHealth <= 0.0f)
	{
		OnOutOfHealth.Broadcast(nullptr, nullptr, nullptr, EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentHealth);
	}

	bOutOfHealth = (CurrentHealth <= 0.0f);
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