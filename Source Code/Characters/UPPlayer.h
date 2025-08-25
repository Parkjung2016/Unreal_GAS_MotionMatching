// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UPCharacterBase.h"
#include "GameplayTags.h"
#include "UPPlayer.generated.h"

struct FInputActionValue;

UCLASS()
class UP_API AUPPlayer : public AUPCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUPPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region InputSystem

private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Look(const FInputActionValue& InputValue);
	void Input_Run(const FInputActionValue& InputValue);

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UUPInputConfig> InputConfigDataAsset;

#pragma endregion

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;
};
