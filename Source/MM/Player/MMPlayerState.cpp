// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MMPlayerState.h"
#include "AbilitySystem/AttributeSet/MMAttributeSet.h"

#include "AbilitySystemComponent.h"

AMMPlayerState::AMMPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));

	AttributeSet = CreateDefaultSubobject<UMMAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AMMPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
