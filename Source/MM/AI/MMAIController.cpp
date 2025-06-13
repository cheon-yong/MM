// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MMAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMMAIController::HomePosKey(TEXT("HomePos"));
const FName AMMAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AMMAIController::TargetKey(TEXT("Target"));

AMMAIController::AMMAIController()
{
}

void AMMAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AMMAIController::RunAI()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BlackBoardAsset, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, GetPawn()->GetActorLocation());
		if (!RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
	Blackboard = BlackboardComp;
}

void AMMAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
