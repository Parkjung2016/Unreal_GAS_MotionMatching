// Fill out your copyright notice in the Description page of Project Settings.


#include "UPWeaponBase.h"


// Sets default values
AUPWeaponBase::AUPWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultWeaponMeshRef(
	TEXT(
		"Script/Engine.StaticMesh'/Game/_Art/YI_NPC/Meshes/Human_Shared/Weapons/SM_Sword.SM_Sword'"));
	if (DefaultWeaponMeshRef.Succeeded())
	{
		WeaponMesh->SetStaticMesh(DefaultWeaponMeshRef.Object);
	}
}

// Called when the game starts or when spawned
void AUPWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}
