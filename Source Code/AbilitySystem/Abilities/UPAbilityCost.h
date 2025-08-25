// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "UObject/Object.h"
#include "UPAbilityCost.generated.h"

class UUPGameplayAbility;

/**
 * 
 */
UCLASS(MinimalAPI, DefaultToInstanced, EditInlineNew, Abstract)
class UUPAbilityCost : public UObject
{
	GENERATED_BODY()
public:
	UUPAbilityCost()
	{
	}
	virtual bool CheckCost(const UUPGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
	{
		return true;
	}
	
	virtual void ApplyCost(const UUPGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
	{
	}

	bool ShouldOnlyApplyCostOnHit() const { return bOnlyApplyCostOnHit; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Costs)
	bool bOnlyApplyCostOnHit = false;
};

