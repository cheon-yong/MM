// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "MMAT_HitTrace.generated.h"

class UGameplayEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHitTraceResultDelegate, const TArray<FHitResult>&, HitResults, const TArray<TSubclassOf<UGameplayEffect>>&, DamageEffects);

/**
 * 
 */
UCLASS()
class MM_API UMMAT_HitTrace : public UAbilityTask
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "Perform Hit Trace", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
    static UMMAT_HitTrace* PerformHitTrace(UGameplayAbility* OwningAbility, AActor* TargetActor, float AttackRange, TArray<TSubclassOf<UGameplayEffect>>& AppliedEffect, float Delay = 0.0f);

    virtual void Activate() override;

    UPROPERTY(BlueprintAssignable)
    FHitTraceResultDelegate OnHit;

private:
    void PerformTrace();

private:
    UPROPERTY()
    TObjectPtr<AActor> TargetActor;

    UPROPERTY()
    TArray<TSubclassOf<UGameplayEffect>> AppliedEffect;

    UPROPERTY(Transient)
    float AttackRange = 0.f;
    
    UPROPERTY(Transient)
    float TraceRadius = 0.f;

    UPROPERTY(Transient)
    float TraceDelay = 0.f;
};
