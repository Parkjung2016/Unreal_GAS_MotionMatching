// Fill out your copyright notice in the Description page of Project Settings.


#include "UPCharacterBase.h"

#include "CharacterTrajectoryComponent.h"
#include "UPCharacterCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UP/AbilitySystem/UPAbilitySystemComponent.h"
#include "UP/Player/UPPlayerState.h"
#include "UP/Weapon/UPWeaponBase.h"

// Sets default values
AUPCharacterBase::AUPCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterTrajectory = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("CharTrajectory"));
	CharacterCombat = CreateDefaultSubobject<UUPCharacterCombatComponent>(TEXT("CharCombat"));
	CharacterCombat->ComponentTags = { FName("Combat") };
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

#pragma region Mesh Setting

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshRef(
		TEXT(
			"/Script/Engine.SkeletalMesh'/Game/_Art/YI_NPC/Demo/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	if (MeshRef.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshRef.Object);
	}

	GetMesh()->SetVisibility(false);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	BodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	BodyMesh->SetupAttachment(GetMesh());

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), "weapon_r");

	BeardMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Beard"));
	BeardMesh->SetupAttachment(BodyMesh);

	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	HeadMesh->SetupAttachment(BodyMesh);

	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	HairMesh->SetupAttachment(BodyMesh);

	OutfitMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Outfit"));
	OutfitMesh->SetupAttachment(BodyMesh);

	EyebrowsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Eyebrows"));
	EyebrowsMesh->SetupAttachment(BodyMesh);

	static ConstructorHelpers::FClassFinder<AUPWeaponBase> DefaultWeaponRef(
		TEXT(
			"/Script/Engine.Blueprint'/Game/Blueprints/Weapons/BP_Sword.BP_Sword_C'"));
	if (DefaultWeaponRef.Succeeded())
	{
		Weapon->SetChildActorClass(DefaultWeaponRef.Class);
	}
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultBodyMeshRef(
		TEXT(
			"/Script/Engine.SkeletalMesh'/Game/_Art/YI_NPC/Meshes/Human_M01_Shared/Body/SK_Human_Body.SK_Human_Body'"));
	if (DefaultBodyMeshRef.Succeeded())
	{
		BodyMesh->SetSkeletalMesh(DefaultBodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultHeadMeshRef(
		TEXT(
			"/Script/Engine.SkeletalMesh'/Game/_Art/YI_NPC/Meshes/Human_M01_Shared/Head/SK_Human_Head07.SK_Human_Head07'"));
	if (DefaultHeadMeshRef.Succeeded())
	{
		HeadMesh->SetSkeletalMesh(DefaultHeadMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultHairMeshRef(
		TEXT(
			"/Script/Engine.SkeletalMesh'/Game/_Art/YI_NPC/Meshes/Human_M01_Knight/Hair02_Knight/SK_Human_Hair02_Head07.SK_Human_Hair02_Head07'"));
	if (DefaultHairMeshRef.Succeeded())
	{
		HairMesh->SetSkeletalMesh(DefaultHairMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultOutfitMeshRef(
		TEXT(
			"/Script/Engine.SkeletalMesh'/Game/_Art/YI_NPC/Meshes/Human_M01_Knight/Whole/SK_Human_Knight_Outfit_Cloth.SK_Human_Knight_Outfit_Cloth'"));
	if (DefaultOutfitMeshRef.Succeeded())
	{
		OutfitMesh->SetSkeletalMesh(DefaultOutfitMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultEyebrowsMeshRef(
		TEXT(
			"/Script/Engine.SkeletalMesh'/Game/_Art/YI_NPC/Meshes/Human_M01_Knight/Hair02_Knight/SK_Human_Eyebrows02_Head02.SK_Human_Eyebrows02_Head02'"));
	if (DefaultEyebrowsMeshRef.Succeeded())
	{
		EyebrowsMesh->SetSkeletalMesh(DefaultEyebrowsMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> RetargetPosAnimRef(
		TEXT(
			"/Script/Engine.AnimBlueprint'/Game/_Art/YI_NPC/Blueprints/AnimTools_M01_Human/ABP_RetargetPose.ABP_RetargetPose_C'"));
	if (RetargetPosAnimRef.Succeeded())
	{
		BodyMesh->SetAnimInstanceClass((RetargetPosAnimRef.Class));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> CopyPoseAnimRef(
		TEXT(
			"/Script/Engine.AnimBlueprint'/Game/_Art/YI_NPC/Blueprints/Master/Animation/ABP_CopyPose_NPC.ABP_CopyPose_NPC_C'"));
	if (CopyPoseAnimRef.Succeeded())
	{
		BeardMesh->SetAnimInstanceClass(CopyPoseAnimRef.Class);
		HeadMesh->SetAnimInstanceClass(CopyPoseAnimRef.Class);
		HairMesh->SetAnimInstanceClass(CopyPoseAnimRef.Class);
		OutfitMesh->SetAnimInstanceClass(CopyPoseAnimRef.Class);
		EyebrowsMesh->SetAnimInstanceClass(CopyPoseAnimRef.Class);
	}

#pragma endregion
	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 88.0f);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
}

// Called when the game starts or when spawned
void AUPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if (Weapon)
	{
		AUPWeaponBase* CurrentWeapon = Cast<AUPWeaponBase>(Weapon->GetChildActor());
		CharacterCombat->SetCurrentWeapon(CurrentWeapon);
	}
}

// Called every frame
void AUPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUPCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UUPAbilitySystemComponent* AUPCharacterBase::GetUPAbilitySystemComponent() const
{
	AUPPlayerState* UPPS = GetPlayerState<AUPPlayerState>();
	if (!UPPS)
		return nullptr;
	return Cast<UUPAbilitySystemComponent>(UPPS->GetAbilitySystemComponent());
}

UAbilitySystemComponent* AUPCharacterBase::GetAbilitySystemComponent() const
{
	return GetUPAbilitySystemComponent();
}
