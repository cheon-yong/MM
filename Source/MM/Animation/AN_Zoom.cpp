// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_Zoom.h"
#include "Character/MMPlayerCharacter.h"

void UAN_Zoom::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AMMPlayerCharacter* MMPC = Cast<AMMPlayerCharacter>(MeshComp->GetOwner()))
	{
		UCurveFloat* CurveToUse = bUsingCurve ? Curve : nullptr;
		MMPC->Zoom(ZoomTime, TargetFOV, CurveToUse);
	}
}