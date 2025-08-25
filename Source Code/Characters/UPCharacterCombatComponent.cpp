// Fill out your copyright notice in the Description page of Project Settings.


#include "UPCharacterCombatComponent.h"

#include "UPCharacterBase.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UP/Weapon/UPWeaponBase.h"


// Sets default values for this component's properties
UUPCharacterCombatComponent::UUPCharacterCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetAutoActivate(true);

	// ...
}


// Called when the game starts
void UUPCharacterCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UUPCharacterCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	PerformWeaponTrace();
}

void UUPCharacterCombatComponent::WeaponTrace(bool WeaponTraceOn)
{
	UE_LOG(LogTemp, Warning, TEXT("WeaponMesh"));

	bWeaponTrace = WeaponTraceOn;
}

void UUPCharacterCombatComponent::SetCurrentWeapon(class AUPWeaponBase* Weapon)
{
	CurrentWeapon = Weapon;
}

void UUPCharacterCombatComponent::PerformWeaponTrace()
{
	if (!bWeaponTrace)return;
	if (!CurrentWeapon) return;
	UStaticMeshComponent* WeaponMesh = CurrentWeapon->GetWeaponMesh();
	FVector TopTraceVec = WeaponMesh->GetSocketLocation("TopTrace");
	FVector BottomTraceVec = WeaponMesh->GetSocketLocation("BottomTrace");
	float TraceSize = 30.f;
	FHitResult OutResult;
	TArray<AActor*> IgnoreActors;
	bool bResult = UKismetSystemLibrary::BoxTraceSingle(this, TopTraceVec, BottomTraceVec, FVector::One() * TraceSize,
	                                                    FRotator::ZeroRotator, ETraceTypeQuery::TraceTypeQuery3, false,
	                                                    IgnoreActors,
	                                                    EDrawDebugTrace::None, OutResult, true);
	if (bResult)
	{
		ACharacter* CharacterActor = Cast<ACharacter>(OutResult.GetActor());
		if (CharacterActor)
		{
			FDamageEvent DamageEvent;

			CharacterActor->TakeDamage(15, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
			bWeaponTrace = false;
		}
	}
}
