// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Abilities/GameplayAbility.h"
#include "UPGameplayAbility.generated.h"

#define UE_API UP_API

struct FGameplayAbilityActivationInfo;
struct FGameplayAbilitySpec;
struct FGameplayAbilitySpecHandle;

class AActor;
class AController;
class AUPCharacterBase;
class AUPPlayerController;
class APlayerController;
class FText;
class UAnimMontage;
class UUPAbilityCost;
class UUPAbilitySystemComponent;
class UObject;
struct FFrame;
struct FGameplayAbilityActorInfo;
struct FGameplayEffectSpec;
struct FGameplayEventData;

UENUM(BlueprintType)
enum class EUPAbilityActivationPolicy : uint8
{
	OnInputTriggered,

	WhileInputActive,

	OnSpawn
};

UENUM(BlueprintType)
enum class EUPAbilityActivationGroup : uint8
{
	Independent,

	Exclusive_Replaceable,

	Exclusive_Blocking,

	MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FUPAbilityMontageFailureMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> AvatarActor = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer FailureTags;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimMontage> FailureMontage = nullptr;
};

UCLASS(MinimalAPI, Abstract, HideCategories = Input)
class UUPGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	friend class UUPAbilitySystemComponent;

public:
	UE_API UUPGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "UP|Ability")
	UE_API UUPAbilitySystemComponent* GetUPAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "UP|Ability")
	UE_API AUPPlayerController* GetUPPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "UP|Ability")
	UE_API AController* GetControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "UP|Ability")
	UE_API AUPCharacterBase* GetUPCharacterFromActorInfo() const;

	EUPAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
	EUPAbilityActivationGroup GetActivationGroup() const { return ActivationGroup; }

	UE_API void TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo,
	                                      const FGameplayAbilitySpec& Spec) const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "UP|Ability",
		Meta = (ExpandBoolAsExecs = "ReturnValue"))
	UE_API bool CanChangeActivationGroup(EUPAbilityActivationGroup NewGroup) const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "UP|Ability",
		Meta = (ExpandBoolAsExecs = "ReturnValue"))
	UE_API bool ChangeActivationGroup(EUPAbilityActivationGroup NewGroup);

	void OnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const
	{
		NativeOnAbilityFailedToActivate(FailedReason);
		ScriptOnAbilityFailedToActivate(FailedReason);
	}

protected:
	UE_API virtual void NativeOnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const;

	UFUNCTION(BlueprintImplementableEvent)
	UE_API void ScriptOnAbilityFailedToActivate(const FGameplayTagContainer& FailedReason) const;

	//~UGameplayAbility interface
	UE_API virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	                                       const FGameplayAbilityActorInfo* ActorInfo,
	                                       const FGameplayTagContainer* SourceTags,
	                                       const FGameplayTagContainer* TargetTags,
	                                       FGameplayTagContainer* OptionalRelevantTags) const override;
	UE_API virtual void SetCanBeCanceled(bool bCanBeCanceled) override;
	UE_API virtual void
	OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	UE_API virtual void
	OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	UE_API virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                              OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	UE_API virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                              const FGameplayAbilityActivationInfo ActivationInfo) const override;
	UE_API virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent,
	                                                      const FGameplayTagContainer* SourceTags = nullptr,
	                                                      const FGameplayTagContainer* TargetTags = nullptr,
	                                                      OUT FGameplayTagContainer* OptionalRelevantTags = nullptr)
	const override;
	//~End of UGameplayAbility interface

	UE_API virtual void OnPawnAvatarSet();


	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityAdded")
	UE_API void K2_OnAbilityAdded();

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnAbilityRemoved")
	UE_API void K2_OnAbilityRemoved();

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnPawnAvatarSet")
	UE_API void K2_OnPawnAvatarSet();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UP|Ability Activation")
	EUPAbilityActivationPolicy ActivationPolicy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UP|Ability Activation")
	EUPAbilityActivationGroup ActivationGroup;

	UPROPERTY(EditDefaultsOnly, Instanced, Category = Costs)
	TArray<TObjectPtr<UUPAbilityCost>> AdditionalCosts;

	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	TMap<FGameplayTag, FText> FailureTagToUserFacingMessages;

	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> FailureTagToAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Advanced")
	bool bLogCancelation;
};
#undef UE_API
