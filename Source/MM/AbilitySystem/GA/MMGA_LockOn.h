// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MMGA_LockOn.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MM_API UMMGA_LockOn : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
    UMMGA_LockOn();

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData) override;

private:
    AActor* FindClosestTarget() const;
};
