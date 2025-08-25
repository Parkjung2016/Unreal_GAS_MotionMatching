// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "UPPlayerState.generated.h"

#define UE_API UP_API

class AController;
class AUPPlayerController;
class APlayerState;
class FName;
class UAbilitySystemComponent;
class UUPAbilitySystemComponent;
class UObject;
class UUPAbilitySet;
struct FFrame;
struct FGameplayTag;
/**
 * 
 */
UCLASS(MinimalAPI, Config = Game)
class AUPPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UE_API AUPPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "UP|PlayerState")
	UE_API AUPPlayerController* GetUPPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "UP|PlayerState")
	UUPAbilitySystemComponent* GetUPAbilitySystemComponent() const { return AbilitySystemComponent; }

	UE_API virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UE_API virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "UP|PlayerState")
	TObjectPtr<UUPAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "UP|PlayerState")
	TObjectPtr<const UUPAbilitySet> AbilitySet;
};

#undef UE_API
