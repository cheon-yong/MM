// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AN_HitTrace.h"

#include "AbilitySystem/GA/MMGA_CombatBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAN_HitTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner()))
	{
		TArray<FGameplayAbilitySpec> Specs = ASC->GetActivatableAbilities();
		
		FGameplayTagContainer Container;
		Container.AddTag(GATag);

		for (const FGameplayAbilitySpec& Spec : Specs)
		{
			FGameplayTagContainer& Tags = Spec.Ability->AbilityTags;

			if (Spec.IsActive() && Tags.HasAllExact(Container))
			{
				for (UGameplayAbility* InstancedAbility : Spec.GetAbilityInstances())
				{
					if (InstancedAbility && InstancedAbility->AbilityTags.HasAllExact(Container))
					{
						if (UMMGA_CombatBase* CombatGA = Cast<UMMGA_CombatBase>(InstancedAbility))
						{
							CombatGA->HitCheck(); 
						}
					}
				}
			}
		}
	}

}
