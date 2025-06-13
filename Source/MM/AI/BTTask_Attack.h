// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "GameplayAbilitySpec.h"

#include "BTTask_Attack.generated.h"

class UGameplayAbility;
struct FAbilityEndedData;

/**
 * 
 */
UCLASS()
class MM_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnAbilityEnded(const FAbilityEndedData& AbilityEndedData);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AttackTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBehaviorTreeComponent* CachedOwnerComp;
};
