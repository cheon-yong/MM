// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/MMCharacter.h"
#include "MMNonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MM_API AMMNonPlayerCharacter : public AMMCharacter
{
	GENERATED_BODY()
	
public:
	AMMNonPlayerCharacter();

protected:
	virtual void BeginPlay() override;
	
	void OnBreak(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);

	void OnHealthZero(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;
};
