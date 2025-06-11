// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MMNumberPopActor.h"
#include "Widget/MMWidgetComponent.h"
#include "Widget/MMNumberPopSubsystem.h"
#include "Widget/MMNumberPopText.h"

// Sets default values
AMMNumberPopActor::AMMNumberPopActor()
{
	NumberPop = CreateDefaultSubobject<UMMWidgetComponent>(TEXT("NumberPop"));

}

void AMMNumberPopActor::BeginPlay()
{
	Super::BeginPlay();

}

void AMMNumberPopActor::Deactivate()
{
	if (UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if (UMMNumberPopSubsystem* Subsystem = GameInstance->GetSubsystem<UMMNumberPopSubsystem>())
		{
			Subsystem->ReturnActor(this);
		}
	}
}

void AMMNumberPopActor::SetNumberText(float Damage)
{
	if (auto* NumberText = Cast<UMMNumberPopText>(NumberPop->GetWidget()))
	{
		NumberText->SetNumberText(Damage);
	}
}