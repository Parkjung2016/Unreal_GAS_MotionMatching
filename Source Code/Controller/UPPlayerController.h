// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UPPlayerController.generated.h"

class UUPAbilitySystemComponent;
class AUPPlayerState;
/**
 * 
 */
UCLASS()
class UP_API AUPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUPPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

public:
	UFUNCTION(BlueprintCallable, Category = "UP|PlayerController")
	 AUPPlayerState* GetUPPlayerState() const;
	UFUNCTION(BlueprintCallable, Category = "UP|PlayerController")
	UUPAbilitySystemComponent* GetUPAbilitySystemComponent() const;

protected:
	virtual void BeginPlay() override;
};
