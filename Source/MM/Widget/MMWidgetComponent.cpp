// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MMWidgetComponent.h"
#include "Widget/MMUserWidget.h"

void UMMWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UMMUserWidget* MMUserWidget = Cast<UMMUserWidget>(GetWidget());
	if (MMUserWidget)
	{
		MMUserWidget->SetAbilitySystemComponent(GetOwner());
	}
}