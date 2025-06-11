// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/MMNumberPopSubsystem.h"
#include "Actor/MMNumberPopActor.h"

UMMNumberPopSubsystem::UMMNumberPopSubsystem()
{
    static ConstructorHelpers::FClassFinder<AMMNumberPopActor> ActorBP(TEXT("/Game/Blueprint/Actor/BP_NumberPop"));
    if (ActorBP.Succeeded())
    {
        NumberPopActorClass = ActorBP.Class;
    }
}

void UMMNumberPopSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    CreateActors(InitialSize);
}

void UMMNumberPopSubsystem::Deinitialize()
{
	Super::Deinitialize();
    ActorPool.Empty();
}

AMMNumberPopActor* UMMNumberPopSubsystem::GetOrCreateActor()
{
    if (ActorPool.IsEmpty())
    {
        CreateActors(InitialSize);
    }

    AMMNumberPopActor* OutActor;
    ActorPool.Dequeue(OutActor);
    OutActor->SetHidden(false);
	return OutActor;
}

void UMMNumberPopSubsystem::ReturnActor(AMMNumberPopActor* Actor)
{
    Actor->SetHidden(true);
    ActorPool.Enqueue(Actor);
}

void UMMNumberPopSubsystem::CreateActors(int Number)
{
    if (NumberPopActorClass)
    {
        auto World = GetWorld();
        for (int i = 0; i < InitialSize; i++)
        {
            FActorSpawnParameters Params;
            Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            FVector SpawnLocation = FVector::ZeroVector;
            FRotator SpawnRotation = FRotator::ZeroRotator;

            AMMNumberPopActor* Actor = World->SpawnActor<AMMNumberPopActor>(NumberPopActorClass, SpawnLocation, SpawnRotation, Params);
            if (Actor)
            {
                ReturnActor(Actor);
            }
        }
    }
}
