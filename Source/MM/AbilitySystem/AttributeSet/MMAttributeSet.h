// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MMAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_SixParams(FMMAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, const FGameplayEffectSpec* /*EffectSpec*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/);

/**
 * 
 */
UCLASS()
class MM_API UMMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMMAttributeSet();

	ATTRIBUTE_ACCESSORS(UMMAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, AttackRadius);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, MaxAttackSpeed);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, BreakGauge);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, MaxBreakGauge);
	ATTRIBUTE_ACCESSORS(UMMAttributeSet, Damage);

	// Delegate when health changes due to damage/healing, some information may be missing on the client
	mutable FMMAttributeEvent OnHealthChanged;

	// Delegate when max health changes
	mutable FMMAttributeEvent OnMaxHealthChanged;

	// Delegate when health changes due to damage/healing, some information may be missing on the client
	mutable FMMAttributeEvent OnStaminaChanged;

	// Delegate when max health changes
	mutable FMMAttributeEvent OnMaxStaminaChanged;

	// Delegate when health changes due to damage/healing, some information may be missing on the client
	mutable FMMAttributeEvent OnBreakGaugeChanged;

	// Delegate when max health changes
	mutable FMMAttributeEvent OnMaxBreakGaugeChanged;

	// Delegate to broadcast when the health attribute reaches zero
	mutable FMMAttributeEvent OnOutOfHealth;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	//virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BreakGauge(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxBreakGauge(const FGameplayAttributeData& OldValue);

protected:
	bool bOutOfHealth;

	// Store the health before any changes 
	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;

	float MaxStaminaBeforeAttributeChange;
	float StaminaBeforeAttributeChange;

	float MaxBreakGaugeBeforeAttributeChange;
	float BreakGaugeBeforeAttributeChange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxAttackSpeed;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BreakGauge, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BreakGauge;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxBreakGauge, Category = "Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxBreakGauge;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

};
