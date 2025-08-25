// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UPWeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUPWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UP_API IUPWeaponInterface 
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void WeaponTrace(bool WeaponTraceOn) =0;
};
