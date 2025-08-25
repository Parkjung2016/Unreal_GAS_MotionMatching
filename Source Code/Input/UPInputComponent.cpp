// Fill out your copyright notice in the Description page of Project Settings.


#include "UPInputComponent.h"

UUPInputComponent::UUPInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void UUPInputComponent::AddInputMappings(const UUPInputConfig* InputConfig,
										   UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to add something from your input config if required
}

void UUPInputComponent::RemoveInputMappings(const UUPInputConfig* InputConfig,
											  UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to remove input mappings that you may have added above
}

void UUPInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
