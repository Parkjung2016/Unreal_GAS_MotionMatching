// Fill out your copyright notice in the Description page of Project Settings.


#include "UPAttackComboAbility.h"

#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks//AbilityTask_WaitGameplayEvent.h"
#include "UP/UPGamePlayTags.h"
#include "UP/Characters/UPCharacterBase.h"

UUPAttackComboAbility::UUPAttackComboAbility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
	ComboWindowTag(UPGamePlayTags::Player_ComboWindow),
	ComboWindowOpenTag(UPGamePlayTags::Event_ComboWindowOpen),
	ComboWindowEndTag(UPGamePlayTags::Event_ComboWindowEnd)
{
}

void UUPAttackComboAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	bool Result = CommitAbility(Handle, ActorInfo, ActivationInfo);
	if (!Result)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this, TEXT("PlayAttack"), MontageToPlay, 1.f);
	PlayAttackTask->ReadyForActivation();

	ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(PrevComboTag);
	ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(ComboWindowTag);
	UE_LOG(LogTemp, Warning, TEXT("UUPAttackComboAbility::ActivateAbility: %s"),
	       *ComboWindowOpenTag.GetTagName().ToString());
	UAbilityTask_WaitGameplayEvent* WaitComboWindowOpenEvent =
		UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboWindowOpenTag, nullptr, true);
	if (WaitComboWindowOpenEvent)
	{
		WaitComboWindowOpenEvent->EventReceived.AddDynamic(this, &UUPAttackComboAbility::OnComboWindowOpen);
	}
	WaitComboWindowOpenEvent->ReadyForActivation();
	
	UAbilityTask_WaitGameplayEvent* WaitComboWindowEndEvent =
		UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboWindowEndTag, nullptr, true);
	if (WaitComboWindowEndEvent)
	{
		WaitComboWindowEndEvent->EventReceived.AddDynamic(this, &UUPAttackComboAbility::OnComboWindowEnd);
	}
	WaitComboWindowEndEvent->ReadyForActivation();
	
}

void UUPAttackComboAbility::OnComboWindowOpen(FGameplayEventData Payload)
{
	GetCurrentActorInfo()->AbilitySystemComponent->AddLooseGameplayTag(ComboWindowTag);
}

void UUPAttackComboAbility::OnComboWindowEnd(FGameplayEventData Payload)
{
	GetCurrentActorInfo()->AbilitySystemComponent->RemoveLooseGameplayTag(ComboWindowTag);
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
