// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MMNumberPopText.h"
#include "Components/TextBlock.h"

void UMMNumberPopText::SetNumberText(float Damage)
{
	int DamageInt = (int)Damage;
	NumberText->SetText(FText::FromString(FString::Printf(TEXT("%d"), DamageInt)));
}