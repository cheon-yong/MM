// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MMGhostActor.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Kismet/KismetMaterialLibrary.h"


// Sets default values
AMMGhostActor::AMMGhostActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));
}

UE_DISABLE_OPTIMIZATION
void AMMGhostActor::Init(USkeletalMeshComponent* NewMesh)
{
	if (NewMesh == nullptr)
	{
		return;
	}

	PoseableMesh->SetSkeletalMesh(NewMesh->GetSkeletalMeshAsset());
	PoseableMesh->CopyPoseFromSkeletalComponent(NewMesh);

	for (int i = 0; i < PoseableMesh->GetMaterials().Num(); i++)
	{
		UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(ColorMat, this);
		Materials.Add(MID);

		PoseableMesh->SetMaterial(i, MID);
	}

	PlayTimeline();
}
UE_ENABLE_OPTIMIZATION
