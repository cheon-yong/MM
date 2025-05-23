// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "MMAT_MoveToTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArrivedAtTargetSignature, AActor*, Target);

class AController;

/**
 * 
 */
UCLASS()
class MM_API UMMAT_MoveToTarget : public UAbilityTask
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintAssignable)
    FOnArrivedAtTargetSignature OnArrived;

    static UMMAT_MoveToTarget* MoveToTarget(UGameplayAbility* OwningAbility, AActor* Target, float AcceptanceRadius);

    virtual void Activate() override;
    void CheckDistance();
    virtual void TickTask(float DeltaTime) override;
    virtual void OnDestroy(bool bInOwnerFinished) override;

    void EndTask(bool bSuccess);

private:
    UPROPERTY()
    TWeakObjectPtr<AActor> TargetActor;

    UPROPERTY()
    TObjectPtr<AController> AvatarController;

    float AcceptRadius = 100.f;
    float RecheckInterval = 0.1f;
    float TimeSinceLastCheck = 0.f;
};
