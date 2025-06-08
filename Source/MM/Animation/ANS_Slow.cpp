// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ANS_Slow.h"

void UANS_Slow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
	{
		if (UAnimMontage* AnimMontage = Cast<UAnimMontage>(Animation))
		{
			AnimInstance->Montage_SetPlayRate(AnimMontage, TargetRate);
		}
	}

}

void UANS_Slow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
	{
		if (UAnimMontage* AnimMontage = Cast<UAnimMontage>(Animation))
		{
			AnimInstance->Montage_SetPlayRate(AnimMontage, 1.0f);
		}
	}
}
