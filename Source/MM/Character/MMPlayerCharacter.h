// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/MMCharacter.h"
#include "AbilitySystemInterface.h"
#include "MMPlayerCharacter.generated.h"


class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class MM_API AMMPlayerCharacter : public AMMCharacter
{
	GENERATED_BODY()

public:
	AMMPlayerCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void PossessedBy(AController* NewController) override;


public:
	UPROPERTY(EditAnywhere, Category = GAS)
	TMap<int32, TSubclassOf<UGameplayAbility>> StartInputAbilities;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;


};
