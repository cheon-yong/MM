// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MMPlayerState.h"

#include "AbilitySystemComponent.h"

AMMPlayerState::AMMPlayerState()
{
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
}

UAbilitySystemComponent* AMMPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}
