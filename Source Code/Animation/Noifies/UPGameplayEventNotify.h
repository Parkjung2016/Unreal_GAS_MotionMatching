// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "UPGameplayEventNotify.generated.h"

/**
 * 
 */
UCLASS()
class UP_API UUPGameplayEventNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag EventTag;
};
