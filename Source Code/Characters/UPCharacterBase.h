// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "UPCharacterBase.generated.h"

class UUPAbilitySystemComponent;

UCLASS()
class UP_API AUPCharacterBase : public ACharacter, public IAbilitySystemInterface

{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUPCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	class UCharacterTrajectoryComponent* GetCharacterTrajectoryComponent() const { return CharacterTrajectory; }
	class UUPCharacterCombatComponent* GetCharacterCombatComponent() const { return CharacterCombat; }
	UFUNCTION(BlueprintCallable, Category = "UP|Character")
	UUPAbilitySystemComponent* GetUPAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
#pragma  region Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> BodyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> BeardMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> HeadMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> HairMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> OutfitMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> EyebrowsMesh;
#pragma  endregion
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCharacterTrajectoryComponent> CharacterTrajectory;;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UUPCharacterCombatComponent> CharacterCombat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UChildActorComponent> Weapon;
};
