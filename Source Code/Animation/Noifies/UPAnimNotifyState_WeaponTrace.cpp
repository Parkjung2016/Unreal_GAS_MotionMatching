// Fill out your copyright notice in the Description page of Project Settings.


#include "UPAnimNotifyState_WeaponTrace.h"

#include "UP/Weapon/UPWeaponInterface.h"

void UUPAnimNotifyState_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                 float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp)return;
	if (!MeshComp->GetOwner())return;

	IUPWeaponInterface* WeaponInterface = Cast<IUPWeaponInterface>(
		MeshComp->GetOwner()->FindComponentByTag<UActorComponent>(FName("Combat")));
	if (!WeaponInterface)return;
	WeaponInterface->WeaponTrace(true);
}

void UUPAnimNotifyState_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp)return;
	if (!MeshComp->GetOwner())return;

	IUPWeaponInterface* WeaponInterface = Cast<IUPWeaponInterface>(
		MeshComp->GetOwner()->FindComponentByTag<UActorComponent>(FName("Combat")));
	if (!WeaponInterface)return;

	WeaponInterface->WeaponTrace(false);
}
