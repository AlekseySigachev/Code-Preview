// Copyright Epic Games, Inc. All Rights Reserved.

#include "Daren/Public/Character/DarenCharacter.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UserInterface/DarenDialogueBoxWidget.h"
#include "UserInterface/DarenHUDWidget.h"

DEFINE_LOG_CATEGORY_STATIC(DarenCharacter, All, All);

ADarenCharacter::ADarenCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create Interaction Box
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Box"));
	InteractBox->SetupAttachment(GetRootComponent());

	//Create Health Component
	HealthComponent = CreateDefaultSubobject<UDarenHealthComponent>(TEXT("Health Component"));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ADarenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADarenCharacter::OnInteract);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
}

void ADarenCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ADarenCharacter::BeginPlay()
{
	Super::BeginPlay();
	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &ADarenCharacter::OnBoxBeginOverlap);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &ADarenCharacter::OnBoxEndOverlap);
	HUD = CreateWidget<UDarenHUDWidget>(GetWorld(), HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}

void ADarenCharacter::OnInteract()
{
	if (InteractableActor)
	{
		UE_LOG(DarenCharacter, Display, TEXT("Try to interact with %s"), *InteractableActor->GetName());
		InteractionInterface =  Cast<IDarenInteractInterface>(InteractableActor);
		if (InteractionInterface)
		{
			InteractionInterface->OnInteract();
		}
	}
}

bool ADarenCharacter::GetIsInAction() const
{
	return bIsInAction;
}


void ADarenCharacter::OnBoxBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
                                        UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	InteractableActor = Actor;
}

void ADarenCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractableActor = nullptr;
}
