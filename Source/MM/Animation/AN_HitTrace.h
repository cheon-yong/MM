// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AN_HitTrace.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class UAN_HitTrace : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag GATag;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<TSubclassOf<UGameplayEffect>> DamageEffects;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
