// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MMAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;
/**
 * 
 */
UCLASS()
class MM_API AMMAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMMAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	UFUNCTION(BlueprintCallable)
	void RunAI();

	UFUNCTION(BlueprintCallable)
	void StopAI();


protected:
	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	UBlackboardData* BlackBoardAsset;
};
