// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MMUserWidget.h"
#include "MMStatusBar.generated.h"


class UMMCharacterHpBar;
class UMMCharacterBreakBar;

/**
 * 
 */
UCLASS()
class MM_API UMMStatusBar : public UMMUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void SetAbilitySystemComponent(AActor* InOwner) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UMMCharacterHpBar> HpBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMMCharacterBreakBar> BreakBar;
};
