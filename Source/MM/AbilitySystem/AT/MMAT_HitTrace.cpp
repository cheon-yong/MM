// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AT/MMAT_HitTrace.h"

#include "AbilitySystem/AttributeSet/MMAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

UMMAT_HitTrace* UMMAT_HitTrace::PerformHitTrace(UGameplayAbility* OwningAbility, AActor* TargetActor, float AttackRange, float Delay)
{
	UMMAT_HitTrace* Task = NewAbilityTask<UMMAT_HitTrace>(OwningAbility);
	Task->TargetActor = TargetActor;
	Task->TraceDelay = Delay;
    Task->AttackRange = AttackRange;
	return Task;
}

void UMMAT_HitTrace::Activate()
{
	Super::Activate();

    if (TraceDelay > 0.f)
    {
        GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
            {
                PerformTrace();
                EndTask();
            });
    }
    else
    {
        PerformTrace();
        EndTask();
    }
}

void UMMAT_HitTrace::PerformTrace()
{
    AActor* Avatar = GetAvatarActor();
    if (!Avatar) return;

    USkeletalMeshComponent* MeshComp = Avatar->FindComponentByClass<USkeletalMeshComponent>();
    if (!MeshComp) return;

    FVector Start = Avatar->GetActorLocation();
    FVector End = Avatar->GetActorLocation();
    // AttackRagne

    if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Avatar))
    {
        const UMMAttributeSet* AttributeSet = ASC->GetSet<UMMAttributeSet>();
        End += Avatar->GetActorForwardVector() * (AttributeSet->GetAttackRange() + AttackRange);
        TraceRadius = AttributeSet->GetAttackRadius();
    }

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Avatar);

    TArray<FHitResult> HitResults;

    GetWorld()->SweepMultiByChannel(
        HitResults,
        Start,
        End,
        FQuat::Identity,
        ECC_GameTraceChannel1, // 원하는 채널로 변경
        FCollisionShape::MakeSphere(TraceRadius),
        Params
    );

//#if WITH_EDITOR
//    DrawDebugSphere(GetWorld(), Start, TraceRadius, 12, FColor::Green, false, 1.f);
//    DrawDebugSphere(GetWorld(), End, TraceRadius, 12, FColor::Red, false, 1.f);
//    DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 1.f);
//#endif

    if (HitResults.Num() > 0)
    {
        OnHit.Broadcast(HitResults);
    }
}
