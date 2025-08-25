#include "UPAbilitySet.h"

#include "UPAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UPAbilitySet)

void FUPAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FUPAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		GameplayEffectHandles.Add(Handle);
	}
}

void FUPAbilitySet_GrantedHandles::AddAttributeSet(UAttributeSet* Set)
{
	GrantedAttributeSets.Add(Set);
}

void FUPAbilitySet_GrantedHandles::TakeFromAbilitySystem(UUPAbilitySystemComponent* UPASC)
{
	check(UPASC);

	if (!UPASC->IsOwnerActorAuthoritative())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			UPASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			UPASC->RemoveActiveGameplayEffect(Handle);
		}
	}

	for (UAttributeSet* Set : GrantedAttributeSets)
	{
		UPASC->RemoveSpawnedAttribute(Set);
	}

	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
	GrantedAttributeSets.Reset();
}

UUPAbilitySet::UUPAbilitySet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUPAbilitySet::GiveToAbilitySystem(UUPAbilitySystemComponent* UPASC,
                                        FUPAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject) const
{
	check(UPASC);
	if (!UPASC->IsOwnerActorAuthoritative())
	{
		return;
	}

	for (int32 SetIndex = 0; SetIndex < GrantedAttributes.Num(); ++SetIndex)
	{
		const FUPAbilitySet_AttributeSet& SetToGrant = GrantedAttributes[SetIndex];

		if (!IsValid(SetToGrant.AttributeSet))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedAttributes[%d] on ability set [%s] is not valid"), SetIndex,
			       *GetNameSafe(this));
			continue;
		}

		UAttributeSet* NewSet = NewObject<UAttributeSet>(UPASC->GetOwner(), SetToGrant.AttributeSet);
		UPASC->AddAttributeSetSubobject(NewSet);
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAttributeSet(NewSet);
		}
	}
	for (int32 SetIndex = 0; SetIndex < GrantedEffects.Num(); ++SetIndex)
	{
		const FUPAbilitySet_EffectSet& SetToGrant = GrantedEffects[SetIndex];

		if (!IsValid(SetToGrant.EffectSet))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedEffects[%d] on effect set [%s] is not valid"), SetIndex,
			       *GetNameSafe(this));
			continue;
		}

		UGameplayEffect* NewSet = NewObject<UGameplayEffect>(UPASC->GetOwner(), SetToGrant.EffectSet);
		UPASC->ApplyGameplayEffectToSelf(NewSet, SetToGrant.EffectLevel, UPASC->MakeEffectContext());
	}


	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FUPAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex,
			       *GetNameSafe(this));
			continue;
		}

		UUPGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UUPGameplayAbility>();
		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = UPASC->GiveAbility(AbilitySpec);

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}
