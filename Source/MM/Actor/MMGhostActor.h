// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MMGhostActor.generated.h"

class UPoseableMeshComponent;
class UMaterialInstance;
class UMaterialInstanceDynamic;
class USkeletalMeshComponent;

UCLASS()
class MM_API AMMGhostActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMMGhostActor();

	void Init(USkeletalMeshComponent* NewMesh);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayTimeline();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPoseableMeshComponent> PoseableMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMaterialInstance> ColorMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInstanceDynamic*> Materials;
};
