// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UP/Weapon/UPWeaponInterface.h"
#include "UPCharacterCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UP_API UUPCharacterCombatComponent : public UActorComponent, public IUPWeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUPCharacterCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void WeaponTrace(bool WeaponTraceOn) override;

public:
	void SetCurrentWeapon(class AUPWeaponBase* Weapon);

private:
	void PerformWeaponTrace();

private:
	bool bWeaponTrace = false;

	TObjectPtr<class AUPWeaponBase> CurrentWeapon;
};
