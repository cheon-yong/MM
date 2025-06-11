// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget/MMUserWidget.h"
#include "MMNumberPopText.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class UMMNumberPopText : public UMMUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SetNumberText(float Damage);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NumberText;
};
