// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget/MMUserWidget.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"

#include "MMSkillButton.generated.h"

struct FGameplayTag;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class MM_API UMMSkillButton : public UMMUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void BindOnAppliedEffect();

	void OnEffectAdded(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle Handle);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCoolTime(float InDuration);
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill, meta = (BindWidget))
	TObjectPtr<UButton> SkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill, meta = (BindWidget))
	TObjectPtr<UTextBlock> CoolTimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	bool bCooldown = false;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	float Duration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	FGameplayTag SkillTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
	FGameplayTag CooldownTag;
};
