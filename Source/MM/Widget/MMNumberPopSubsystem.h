// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "MMNumberPopSubsystem.generated.h"

class AMMNumberPopActor;

/**
 * 
 */
UCLASS(config = Game)
class MM_API UMMNumberPopSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    UMMNumberPopSubsystem();

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable)
    AMMNumberPopActor* GetOrCreateActor();

    UFUNCTION(BlueprintCallable)
    void ReturnActor(AMMNumberPopActor* Actor);

protected:
    void CreateActors(int Number);

private:
    /** 미리 만들어 놓은 위젯 리스트 */
    TQueue<AMMNumberPopActor*> ActorPool;

    /** 위젯 블루프린트 클래스 */
    UPROPERTY()
    TSubclassOf<AMMNumberPopActor> NumberPopActorClass;

    /** 풀 크기 또는 생성 갯수 제한 설정 */
    int32 InitialSize = 10;
};
