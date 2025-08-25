// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UPAttributeSet.h"
#include "UPSpeedSet.generated.h"

/**
 * 
 */
UCLASS()
class UP_API UUPSpeedSet : public UUPAttributeSet
{
	GENERATED_BODY()

public:
	UUPSpeedSet();

	ATTRIBUTE_ACCESSORS(UUPSpeedSet, BaseWalkSpeed);
	ATTRIBUTE_ACCESSORS(UUPSpeedSet, BaseWalkDeceleration);
	ATTRIBUTE_ACCESSORS(UUPSpeedSet, BaseRunSpeed);
	ATTRIBUTE_ACCESSORS(UUPSpeedSet, BaseRunDeceleration);

protected:
	UFUNCTION()
	void OnRep_BaseWalkSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_BaseWalkDeceleration(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_BaseRunSpeed(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_BaseRunDeceleration(const FGameplayAttributeData& OldValue);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseWalkSpeed, Category = "UP|Speed",
		Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseWalkSpeed;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseWalkDeceleration, Category = "UP|Speed",
		Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseWalkDeceleration;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseRunSpeed, Category = "UP|Speed",
		Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseRunSpeed;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BaseRunDeceleration, Category = "UP|Speed",
	Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData BaseRunDeceleration;
};
