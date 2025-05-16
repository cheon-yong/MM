// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GameplayTagContainer.h"
#include "MMCharacter.generated.h"


class UAbilitySystemComponent;
class UGameplayAbility;
class UAutoCombatComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMMCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMMCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// To add mapping context
	virtual void BeginPlay();

protected:
	UPROPERTY(VisibleAnywhere, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InitTags;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	TObjectPtr<UAutoCombatComponent> AutoCombatComponent;
};

