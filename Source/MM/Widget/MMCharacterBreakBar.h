// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget/MMUserWidget.h"
#include "GameplayEffectTypes.h"
#include "MMCharacterBreakBar.generated.h"


class UProgressBar;

/**
 * 
 */
UCLASS(BlueprintType)
class MM_API UMMCharacterBreakBar : public UMMUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;
	
protected:
	virtual void OnBreakChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);
	virtual void OnMaxBreakChanged(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);


	void UpdateBreakBar();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> PbBreakBar;

	float CurrentBreak = 0.0f;
	float CurrentMaxBreak = 0.1f;
};
