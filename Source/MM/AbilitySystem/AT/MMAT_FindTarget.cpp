// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AT/MMAT_FindTarget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystemComponent.h"


UMMAT_FindTarget* UMMAT_FindTarget::FindTarget(UGameplayAbility* OwningAbility, float Radius, FGameplayTag TargetTag)
{
	UMMAT_FindTarget* Task = NewAbilityTask<UMMAT_FindTarget>(OwningAbility);
	Task->SearchRadius = Radius;
    Task->TargetTag = TargetTag;
	return Task;
}

void UMMAT_FindTarget::Activate()
{
	Super::Activate();
	SearchForTarget();
}

UE_DISABLE_OPTIMIZATION
void UMMAT_FindTarget::SearchForTarget()
{
    AActor* OwnerActor = GetAvatarActor();
    if (!OwnerActor) 
    { 
        OnTargetFound.Broadcast(nullptr); 
        EndTask(); 
        return; 
    }

    FVector Origin = OwnerActor->GetActorLocation();
    TArray<FHitResult> Hits;

    // Sphere Overlap using custom object type or enemy collision channel
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

    TArray<AActor*> IgnoreActors;
    IgnoreActors.Add(OwnerActor);

    bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
        this,
        Origin,
        Origin + FVector::UpVector * 0.1f, // very small movement to make a valid trace
        SearchRadius,
        ObjectTypes,
        false,
        IgnoreActors,
        EDrawDebugTrace::None,
        Hits,
        true
    );

    float ClosestDistSq = SearchRadius * SearchRadius;
    AActor* Closest = nullptr;

    for (const FHitResult& Hit : Hits)
    {
        AActor* HitActor = Hit.GetActor();
        if (!HitActor)
            continue;

        UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(HitActor);
        if (!ASC || !ASC->HasMatchingGameplayTag(TargetTag)) 
            continue;

        float DistSq = FVector::DistSquared(Origin, HitActor->GetActorLocation());
        if (DistSq < ClosestDistSq)
        {
            ClosestDistSq = DistSq;
            Closest = HitActor;
        }
    }

    OnTargetFound.Broadcast(Closest);
    EndTask();
}
UE_ENABLE_OPTIMIZATION