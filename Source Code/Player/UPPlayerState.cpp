// Fill out your copyright notice in the Description page of Project Settings.


#include "UPPlayerState.h"

#include "UP/AbilitySystem/UPAbilitySet.h"
#include "UP/AbilitySystem/UPAbilitySystemComponent.h"
#include "UP/Controller/UPPlayerController.h"

AUPPlayerState::AUPPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UUPAbilitySystemComponent>(
		this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	SetNetUpdateFrequency(100.0f);
}

AUPPlayerController* AUPPlayerState::GetUPPlayerController() const
{
	return Cast<AUPPlayerController>(GetOwner());
}

UAbilitySystemComponent* AUPPlayerState::GetAbilitySystemComponent() const
{
	return GetUPAbilitySystemComponent();
}

void AUPPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AUPPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
	}
	if (AbilitySet)
		AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
}
