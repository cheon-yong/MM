// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AI/MMAIController.h"
#include "Character/MMCharacter.h"
#include "Character/MMNonPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	CachedOwnerComp = &OwnerComp;

	auto MMMonster = Cast<AMMNonPlayerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MMMonster)
		return EBTNodeResult::Failed;

	auto Target = Cast<AMMCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMMAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	if (UAbilitySystemComponent* ASC = MMMonster->GetAbilitySystemComponent())
	{
		FGameplayTagContainer TagContainer(AttackTag);
		bool Success = ASC->TryActivateAbilitiesByTag(TagContainer);
		if (Success)
		{
			ASC->OnAbilityEnded.AddUObject(this, &ThisClass::OnAbilityEnded);
			return EBTNodeResult::InProgress;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString("Fail DMASC"));
	}

	return EBTNodeResult::Failed;
}

void UBTTask_Attack::OnAbilityEnded(const FAbilityEndedData& AbilityEndedData)
{
	if (AbilityEndedData.bWasCancelled)
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
	}
	
}