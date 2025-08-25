#pragma once

#include "CoreMinimal.h"
#include "UPGameplayAbility.h"
#include "UPAbilityWithMontage.generated.h"

/**
 * 
 */
UCLASS()
class UP_API UUPAbilityWithMontage : public UUPGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PlayAnimMontage();

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY(BlueprintReadWrite)
	float PlayRate = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	float StartingPosition = 0.0f;
};
