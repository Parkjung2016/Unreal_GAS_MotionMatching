// Fill out your copyright notice in the Description page of Project Settings.


#include "UPGameplayEventNotify.h"

#include "AbilitySystemBlueprintLibrary.h"

void UUPGameplayEventNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                    const FAnimNotifyEventReference& EventReference)
{
	UE_LOG(LogTemp, Warning, TEXT("UUPGameplayEventNotify::Notify: %s"), *EventTag.GetTagName().ToString());
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());;
}
