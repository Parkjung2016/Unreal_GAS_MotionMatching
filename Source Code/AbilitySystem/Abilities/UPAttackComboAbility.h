// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPGameplayAbility.h"
#include "UPAttackComboAbility.generated.h"

/**
 * 
 */
UCLASS()
class UP_API UUPAttackComboAbility : public UUPGameplayAbility
{
	GENERATED_BODY()

	UUPAttackComboAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	void OnComboWindowOpen(FGameplayEventData Payload);
	UFUNCTION()
	void OnComboWindowEnd(FGameplayEventData Payload);

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY(EditAnywhere)
	FGameplayTag PrevComboTag;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGameplayTag ComboWindowTag;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGameplayTag ComboWindowOpenTag;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FGameplayTag ComboWindowEndTag;
};
