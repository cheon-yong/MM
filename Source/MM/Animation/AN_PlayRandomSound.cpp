// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_PlayRandomSound.h"

void UAN_PlayRandomSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (bRandomSound && Sounds.Num() > 1)
	{
		int32 RandomIndex = FMath::RandRange(0, Sounds.Num() - 1);
		Sound = Sounds[RandomIndex];
	}

	Super::Notify(MeshComp, Animation, EventReference);
}
