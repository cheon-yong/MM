// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/WidgetComponent.h"
#include "MMWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MM_API UMMWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
protected:
	virtual void InitWidget() override;
};
