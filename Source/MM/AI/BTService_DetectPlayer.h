// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MM_API UBTService_DetectPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_DetectPlayer();

protected:
	UPROPERTY(EditAnywhere)
	float DetectRadius = 600.0f;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
