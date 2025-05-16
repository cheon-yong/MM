// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AT/MMAT_MoveToTarget.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NavigationSystem.h"

UMMAT_MoveToTarget* UMMAT_MoveToTarget::MoveToTarget(UGameplayAbility* OwningAbility, AActor* Target, float AcceptanceRadius)
{
    UMMAT_MoveToTarget* Task = NewAbilityTask<UMMAT_MoveToTarget>(OwningAbility);
    Task->TargetActor = Target;
    Task->AcceptRadius = AcceptanceRadius;
    return Task;
}

void UMMAT_MoveToTarget::Activate()
{
    Super::Activate();

    ACharacter* Avatar = Cast<ACharacter>(GetAvatarActor());
    if (!Avatar || !TargetActor.IsValid())
    {
        EndTask();
        return;
    }

    AController* Controller = Avatar->GetController();
    if (Controller)
    {
        FVector TargetLocation = TargetActor->GetActorLocation();
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, TargetLocation);
    }

    bTickingTask = true;
}

void UMMAT_MoveToTarget::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    if (!TargetActor.IsValid())
    {
        EndTask();
        return;
    }

    TimeSinceLastCheck += DeltaTime;
    if (TimeSinceLastCheck < RecheckInterval) return;
    TimeSinceLastCheck = 0.f;

    AActor* Avatar = GetAvatarActor();
    float Distance = FVector::Dist(Avatar->GetActorLocation(), TargetActor->GetActorLocation());
    if (Distance <= AcceptRadius)
    {
        OnArrived.Broadcast(TargetActor.Get());
        EndTask();
    }
}

void UMMAT_MoveToTarget::OnDestroy(bool bInOwnerFinished)
{
    bTickingTask = false;
    Super::OnDestroy(bInOwnerFinished);
}
