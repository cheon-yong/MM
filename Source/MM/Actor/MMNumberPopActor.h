// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MMNumberPopActor.generated.h"

class UMMWidgetComponent;
class UMMNumberPopText;

UCLASS()
class MM_API AMMNumberPopActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMMNumberPopActor();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Deactivate();
	
	UFUNCTION(BlueprintCallable)
	void SetNumberText(float Damage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayTextAnimation();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMMWidgetComponent> NumberPop;
};
