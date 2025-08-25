// Fill out your copyright notice in the Description page of Project Settings.


#include "UPSpeedSet.h"

#include "Net/UnrealNetwork.h"

UUPSpeedSet::UUPSpeedSet() : BaseWalkSpeed(200.f), BaseRunSpeed(400.0f)
{
}

void UUPSpeedSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UUPSpeedSet, BaseWalkSpeed, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUPSpeedSet, BaseWalkDeceleration, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUPSpeedSet, BaseRunSpeed, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UUPSpeedSet, BaseRunDeceleration, COND_OwnerOnly, REPNOTIFY_Always);
}

void UUPSpeedSet::OnRep_BaseWalkSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUPSpeedSet, BaseWalkSpeed, OldValue);
}

void UUPSpeedSet::OnRep_BaseWalkDeceleration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUPSpeedSet, BaseWalkDeceleration, OldValue);
}

void UUPSpeedSet::OnRep_BaseRunDeceleration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUPSpeedSet, BaseRunDeceleration, OldValue);
}

void UUPSpeedSet::OnRep_BaseRunSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UUPSpeedSet, BaseRunSpeed, OldValue);
}
