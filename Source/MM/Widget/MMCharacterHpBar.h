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
	
public:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;

protected:
	virtual void OnHealthChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);

	virtual void OnMaxHealthChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWhiteBar();
		
	void UpdateHpBar();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> PbHpBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> PbWhiteBar;

	UPROPERTY(BlueprintReadWrite)
	float BeforeHealth = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float BeforeMaxHealth = 0.1f;

	UPROPERTY(BlueprintReadWrite)
	float CurrentHealth = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float CurrentMaxHealth = 0.1f;

};
