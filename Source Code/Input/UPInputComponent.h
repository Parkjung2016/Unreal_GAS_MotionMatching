// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "UPInputConfig.h"
#include "UPInputComponent.generated.h"


class UEnhancedInputLocalPlayerSubsystem;

UCLASS(Config = Input)
class UP_API UUPInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UUPInputComponent(const FObjectInitializer& ObjectInitializer);

	void AddInputMappings(const UUPInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;
	void RemoveInputMappings(const UUPInputConfig* InputConfig,
	                         UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const;

	template <class UserClass, typename FuncType>
	void BindNativeAction(const UUPInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
	                      UserClass* Object, FuncType Func, bool bLogIfNotFound);

	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UUPInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	                        ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);

	void RemoveBinds(TArray<uint32>& BindHandles);
};


template <class UserClass, typename FuncType>
void UUPInputComponent::BindNativeAction(const UUPInputConfig* InputConfig, const FGameplayTag& InputTag,
                                           ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func,
                                           bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForTag(InputTag, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UUPInputComponent::BindAbilityActions(const UUPInputConfig* InputConfig, UserClass* Object,
                                             PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc,
                                             TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for (const FUPInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc,
				                           Action.InputTag).GetHandle());
			}

			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc,
				                           Action.InputTag).GetHandle());
			}
		}
	}
}
