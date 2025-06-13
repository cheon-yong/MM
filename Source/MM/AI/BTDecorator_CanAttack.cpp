// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CanAttack.h"
#include "AI/MMAIController.h"
#include "Character/MMCharacter.h"
#include "Character/MMNonPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = Cast<AMMNonPlayerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return false;;

	auto Target = Cast<AMMCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMMAIController::TargetKey));
	if (nullptr == Target)
		return false;
	
	bResult = (Target->GetDistanceTo(ControllingPawn) <= AttackRange);
	return bResult;
}
