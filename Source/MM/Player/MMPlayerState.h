// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MMPlayerState.generated.h"

class UAbilitySystemComponent;
class UMMAttributeSet;

/**
 * 
 */
UCLASS()
class MM_API AMMPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMMPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<UAbilitySystemComponent> ASC;

	// Change Attribute
	UPROPERTY()
	TObjectPtr<UMMAttributeSet> AttributeSet;
};
