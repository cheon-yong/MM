// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_TimeDilation.generated.h"

/**
 * 
 */
UCLASS()
class MM_API UAN_TimeDilation : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetDilation = 0.f;
};
