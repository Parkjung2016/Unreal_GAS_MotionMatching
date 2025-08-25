// Fill out your copyright notice in the Description page of Project Settings.


#include "UPAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UP/Characters/UPCharacterBase.h"

UUPAnimInstance::UUPAnimInstance()
{
}

void UUPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AUPCharacterBase>(TryGetPawnOwner());

	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UUPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

FVector2D UUPAnimInstance::GetAOValue() const
{
	if (!Character)
	{
		return FVector2D::ZeroVector;
	}
	FRotator CharacterControlRotation = Character->GetControlRotation();
	FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(CharacterControlRotation,
	                                                                   RootTransform.Rotator());

	FVector LerpValue = UKismetMathLibrary::VLerp(FVector(DeltaRotator.Yaw, DeltaRotator.Pitch, 0.f),
	                                              FVector::ZeroVector, 0.f);
	FVector2D AOValue = FVector2D(LerpValue.X, LerpValue.Y);
	return AOValue;
}

bool UUPAnimInstance::ShouldTurnInPlace() const
{
	if (!Character)return false;
	FRotator CharacterRotation = Character->GetActorRotation();
	FRotator RootRotation = RootTransform.Rotator();

	FRotator DeltaRotator = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, RootRotation);

	return UKismetMathLibrary::Abs(DeltaRotator.Yaw) >= 3;
}

float UUPAnimInstance::VelocitySize2D() const
{
	if (!MovementComponent)return 0.f;
	return MovementComponent->Velocity.SizeSquared2D();
}
