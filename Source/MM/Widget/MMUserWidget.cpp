// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/MMUserWidget.h"
#include "AbilitySystemBlueprintLibrary.h"


void UMMUserWidget::SetAbilitySystemComponent(AActor* InOwner)
{
	if (IsValid(InOwner))
	{
		ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InOwner);
	}
}

UAbilitySystemComponent* UMMUserWidget::GetAbilitySystemComponent() const
{
	return ASC;
}