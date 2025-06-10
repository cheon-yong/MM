// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystemBlueprintLibrary.h"
#include "Widget/MMUserWidget.h"

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