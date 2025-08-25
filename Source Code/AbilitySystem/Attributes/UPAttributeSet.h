// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UPAttributeSet.generated.h"

#define UE_API UP_API
class UUPAbilitySystemComponent;
class AActor;
class UObject;
class UWorld;
struct FGameplayEffectSpec;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_SixParams(FUPAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/,
                                     const FGameplayEffectSpec* /*EffectSpec*/, float /*EffectMagnitude*/,
                                     float /*OldValue*/, float /*NewValue*/);
UCLASS(MinimalAPI)
class UUPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UE_API UUPAttributeSet();

	UE_API UWorld* GetWorld() const override;

	UE_API UUPAbilitySystemComponent* GetUPAbilitySystemComponent() const;
};
#undef UE_API
