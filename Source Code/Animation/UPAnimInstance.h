// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UPAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UP_API UUPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UUPAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION(Blueprintable, BlueprintPure, meta=(BlueprintThreadSafe))
	FVector2D GetAOValue() const;
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	bool ShouldTurnInPlace() const;
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	float VelocitySize2D() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AUPCharacterBase> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

	UPROPERTY(BlueprintReadWrite)
	FTransform RootTransform;
};
