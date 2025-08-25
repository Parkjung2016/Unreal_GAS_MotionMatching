// Fill out your copyright notice in the Description page of Project Settings.


#include "UPAttributeSet.h"

#include "UP/AbilitySystem/UPAbilitySystemComponent.h"

UUPAttributeSet::UUPAttributeSet()
{
}

UWorld* UUPAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UUPAbilitySystemComponent* UUPAttributeSet::GetUPAbilitySystemComponent() const
{
	return Cast<UUPAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
