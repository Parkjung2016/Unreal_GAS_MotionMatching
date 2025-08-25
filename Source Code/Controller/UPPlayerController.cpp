// Fill out your copyright notice in the Description page of Project Settings.


#include "UPPlayerController.h"

#include "UP/AbilitySystem/UPAbilitySystemComponent.h"
#include "UP/Player/UPPlayerState.h"

AUPPlayerController::AUPPlayerController(const FObjectInitializer& ObjectInitializer)
{
}

void AUPPlayerController::BeginPlay()
{
	Super::BeginPlay();
}


void AUPPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	
	if (UUPAbilitySystemComponent* UPASC = GetUPAbilitySystemComponent())
	{
		UPASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

AUPPlayerState* AUPPlayerController::GetUPPlayerState() const
{
	return CastChecked<AUPPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UUPAbilitySystemComponent* AUPPlayerController::GetUPAbilitySystemComponent() const
{
	const AUPPlayerState* UPPS = GetUPPlayerState();
	return (UPPS ? UPPS->GetUPAbilitySystemComponent() : nullptr);
}
