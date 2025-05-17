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
        EndTask(false);
        return;
    }

    AvatarController = Avatar->GetController();
    if (AvatarController == nullptr)
    {
        EndTask(false);
        return;
    }

    CheckDistance();
    UAIBlueprintHelperLibrary::SimpleMoveToActor(AvatarController, TargetActor.Get());

    bTickingTask = true;
}

void UMMAT_MoveToTarget::CheckDistance()
{
    AActor* Avatar = GetAvatarActor();
    float Distance = FVector::Dist(Avatar->GetActorLocation(), TargetActor->GetActorLocation());
    if (Distance <= AcceptRadius)
    {
        EndTask(true);
        return;
    }
}

void UMMAT_MoveToTarget::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    if (!TargetActor.IsValid())
    {
        EndTask(false);
        return;
    }

    TimeSinceLastCheck += DeltaTime;
    if (TimeSinceLastCheck < RecheckInterval) return;
    TimeSinceLastCheck = 0.f;

    CheckDistance();
}

void UMMAT_MoveToTarget::OnDestroy(bool bInOwnerFinished)
{
    bTickingTask = false;
    Super::OnDestroy(bInOwnerFinished);
}

void UMMAT_MoveToTarget::EndTask(bool bSuccess)
{
    if (bSuccess)
    {
        AvatarController->StopMovement();
        AvatarController = nullptr;
    }

    AActor* result = bSuccess ? TargetActor.Get() : nullptr;
    OnArrived.Broadcast(result);
    Super::EndTask();
    return;
}
