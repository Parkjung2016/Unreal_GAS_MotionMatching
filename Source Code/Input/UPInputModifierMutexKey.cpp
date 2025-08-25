// Fill out your copyright notice in the Description page of Project Settings.


#include "UPInputModifierMutexKey.h"
#include "EnhancedPlayerInput.h"


FInputActionValue UUPInputModifierMutexKey::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	const APlayerController* PC = PlayerInput->GetOuterAPlayerController();

	if (!PC)
	{
		return CurrentValue;
	}

	FVector Value = CurrentValue.Get<FVector>();
	if (Key.IsValid() && PC->IsInputKeyDown(Key))
	{
		Value = FVector::ZeroVector;
	}

	return FInputActionValue(CurrentValue.GetValueType(), Value);
}