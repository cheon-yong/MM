// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget/MMUserWidget.h"
#include "GameplayEffectTypes.h"
#include "MMCharacterHpBar.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS(BlueprintType)
class MM_API UMMCharacterHpBar : public UMMUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;

	virtual void OnHealthChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);
	virtual void OnMaxHealthChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);


	void UpdateHpBar();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PbHpBar;

	float CurrentHealth = 0.0f;
	float CurrentMaxHealth = 0.1f;

	//FLinearColor HealthColor = FLinearColor::Red;
};
