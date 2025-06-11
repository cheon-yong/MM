// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MMStatusBar.h"
#include "Widget/MMCharacterHpBar.h"
#include "Widget/MMCharacterBreakBar.h"


void UMMStatusBar::SetAbilitySystemComponent(AActor* InOwner)
{
	Super::SetAbilitySystemComponent(InOwner);

	if (HpBar)
	{
		HpBar->SetAbilitySystemComponent(InOwner);
	}

	if (BreakBar)
	{
		BreakBar->SetAbilitySystemComponent(InOwner);
	}
}
