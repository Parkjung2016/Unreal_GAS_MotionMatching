#include "UPAbilityWithMontage.h"


void UUPAbilityWithMontage::PlayAnimMontage()
{
	const FGameplayAbilitySpecHandle Handle = GetCurrentAbilitySpecHandle();
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	const FGameplayAbilityActivationInfo ActivationInfo = GetCurrentActivationInfo();
	bool Result = CommitAbility(Handle, ActorInfo, ActivationInfo);
	if (!Result)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	AnimInstance->Montage_Play(MontageToPlay, PlayRate, EMontagePlayReturnType::MontageLength, StartingPosition);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
