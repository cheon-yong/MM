// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "MMAIController.h"
#include "Character/MMCharacter.h"
#include "Engine/OverlapResult.h"

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
	NodeName = TEXT("DetectPlayer");
}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory,DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	

	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMMAIController::TargetKey, nullptr);
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			AMMCharacter* MMCharacter = Cast<AMMCharacter>(OverlapResult.GetActor());

			if (MMCharacter && MMCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMMAIController::TargetKey, MMCharacter);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, MMCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), MMCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				return;
			}
		}
	}
}
