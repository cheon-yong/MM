// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_Zoom.generated.h"

/**
 * 
 */
UCLASS()
class MM_API UAN_Zoom : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetFOV = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsingCurve = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bUsingCurve", EditConditionHides))
	TObjectPtr<UCurveFloat> Curve;
};
