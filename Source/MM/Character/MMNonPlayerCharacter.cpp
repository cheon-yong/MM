// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MMNonPlayerCharacter.h"

#include "AbilitySystemComponent.h"

AMMNonPlayerCharacter::AMMNonPlayerCharacter()
{
}

void AMMNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ASC->InitAbilityActorInfo(this, this);

	ASC->AddLooseGameplayTags(InitTags);
}
