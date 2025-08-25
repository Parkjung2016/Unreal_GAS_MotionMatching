// Fill out your copyright notice in the Description page of Project Settings.


#include "UPPlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UP/UPGamePlayTags.h"
#include "UP/AbilitySystem/UPAbilitySystemComponent.h"
#include "UP/AbilitySystem/Attributes/UPSpeedSet.h"
#include "UP/Input/UPInputComponent.h"
#include "UP/Input/UPInputConfig.h"

// Sets default values
AUPPlayer::AUPPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0.f, 55.0f, 0.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->CameraLagSpeed = 8.f;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FObjectFinder<UUPInputConfig> InputConfigDataAssetRef(
		TEXT("/Script/UP.UPInputConfig'/Game/Input/DA_InputConfig.DA_InputConfig'"));
	if (InputConfigDataAssetRef.Succeeded())
	{
		InputConfigDataAsset = InputConfigDataAssetRef.Object;
	}
}

// Called when the game starts or when spawned
void AUPPlayer::BeginPlay()
{
	Super::BeginPlay();

	const UUPSpeedSet* SpeedSet = GetUPAbilitySystemComponent()->GetSet<UUPSpeedSet>();

	if (SpeedSet != nullptr)
	{
		float DefaultSpeed = SpeedSet->GetBaseWalkSpeed();
		float DefaultDeceleration = SpeedSet->GetBaseWalkDeceleration();
		GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
		GetCharacterMovement()->BrakingDecelerationWalking = DefaultDeceleration;
	}
}

// Called every frame
void AUPPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUPPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(InputConfigDataAsset);

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	check(PlayerController);

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(SubSystem);
	SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UUPInputComponent* UPInputComponent = Cast<UUPInputComponent>(PlayerInputComponent);
	check(UPInputComponent);

	TArray<uint32> BindHandles;
	UPInputComponent->BindAbilityActions(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputTagPressed,
	                                     &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

	UPInputComponent->BindNativeAction(InputConfigDataAsset, UPGamePlayTags::InputTag_Move, ETriggerEvent::Triggered,
	                                   this, &ThisClass::Input_Move, true);
	UPInputComponent->BindNativeAction(InputConfigDataAsset, UPGamePlayTags::InputTag_Look, ETriggerEvent::Triggered,
	                                   this, &ThisClass::Input_Look, true);
	UPInputComponent->BindNativeAction(InputConfigDataAsset, UPGamePlayTags::InputTag_Run, ETriggerEvent::Triggered,
	                                   this, &ThisClass::Input_Run, true);
}

void AUPPlayer::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AUPPlayer::Input_Look(const FInputActionValue& InputValue)
{
	const FVector2D LookAxisVector = InputValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.f)
		AddControllerYawInput(LookAxisVector.X);
	if (LookAxisVector.Y != 0.f)
		AddControllerPitchInput(LookAxisVector.Y);
}

void AUPPlayer::Input_Run(const FInputActionValue& InputValue)
{
	bool IsRunning = InputValue.Get<bool>();

	const UUPAbilitySystemComponent* UPASC = GetUPAbilitySystemComponent();
	const UUPSpeedSet* UPSpeedSet = UPASC->GetSet<UUPSpeedSet>();
	float FinalSpeed = IsRunning ? UPSpeedSet->GetBaseRunSpeed() : UPSpeedSet->GetBaseWalkSpeed();
	float FinalDeceleration = IsRunning ? UPSpeedSet->GetBaseRunDeceleration() : UPSpeedSet->GetBaseWalkDeceleration();
	GetCharacterMovement()->MaxWalkSpeed = FinalSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = FinalDeceleration;
}

void AUPPlayer::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (!GetUPAbilitySystemComponent())return;
	GetUPAbilitySystemComponent()->AbilityInputTagPressed(InputTag);
}

void AUPPlayer::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetUPAbilitySystemComponent())return;
	GetUPAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}
