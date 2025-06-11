// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "MMCharacter.generated.h"


class UAbilitySystemComponent;
class UGameplayAbility;
class UAutoCombatComponent;
class UMMAttributeSet;
class AMMGhostActor;
class UMMWidgetComponent;

struct FGameplayEffectSpec;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMMCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMMCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void CreateGhost();

protected:
	// To add mapping context
	virtual void BeginPlay();

	virtual void OnHealthChange(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue);

	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetHitMontage(FGameplayTag ScaleTag);

protected:
	UPROPERTY(VisibleAnywhere, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<UMMAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InitTags;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	TObjectPtr<UAutoCombatComponent> AutoCombatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	TMap<FGameplayTag, UAnimMontage*> HitMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	TSubclassOf<AMMGhostActor> GhostActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	TObjectPtr<UMMWidgetComponent> StatusBarComponent;
};

