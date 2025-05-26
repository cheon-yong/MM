// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_TimeDilation.h"
#include "Character/MMPlayerCharacter.h"

void UAN_TimeDilation::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AMMPlayerCharacter* MMPlayerCharacter = Cast<AMMPlayerCharacter>(MeshComp->GetOwner()))
	{
		MMPlayerCharacter->SetTimeDilation(TargetDilation, Duration);
	}
}
