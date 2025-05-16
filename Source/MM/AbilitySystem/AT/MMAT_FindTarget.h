// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "MMAT_FindTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetFoundSignature, AActor*, Target);

/**
 * 
 */
UCLASS()
class MM_API UMMAT_FindTarget : public UAbilityTask
{
	GENERATED_BODY()

public:

    static UMMAT_FindTarget* FindTarget(UGameplayAbility* OwningAbility, float Radius, FGameplayTag TargetTag);

    virtual void Activate() override;

    UPROPERTY(BlueprintAssignable)
    FTargetFoundSignature OnTargetFound;

private:
    void SearchForTarget();

private:
    float SearchRadius;

    FGameplayTag TargetTag;
    
};
