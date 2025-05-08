// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConclaveCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"


#include "Kismet/GameplayStatics.h" // UGamePlayStatics::
#include "ConclavePlayerController.h"

#include "CharacterComponent/Inventory.h"

#include "Animation/CharacterAnimInstance.h"

#include "CharacterComponent/FirstCameraActor.h"
#include "CharacterComponent/ThirdCameraActor.h"



AConclaveCharacter::AConclaveCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	//GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); //500
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	InitTopDownCamera();
	InitThirdCamera();
	InitFirstCamera();

	

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

	// 값 초기화
	//ThirdCameraComponent->SetActive(true);
	//TopDownCameraComponent->SetActive(false);
}

void AConclaveCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance()); // Mesh가 가지고있는 ABP정보 가져오기
}

void AConclaveCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (Inventory != nullptr) Inventory->AttachCharacter(this);
}
void AConclaveCharacter::SetController_ThirdSight()
{
	UE_LOG(LogTemp, Warning, TEXT("Thid Camera"));
	AConclavePlayerController* playerController;
	playerController = Cast<AConclavePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->ChangeSightType(EPlayerSightType::ThirdSight);

	ThirdCameraComponent->SetActive(true);

	if (FirstCameraComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("First Camera null"));
	}
	else
	{
		FirstCameraComponent->SetActive(false);
	}

	// InputMode 설정
	FInputModeGameOnly InputModeData;
	playerController->SetInputMode(InputModeData);
	playerController->bShowMouseCursor = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction

	GetMesh()->SetVisibility(true);


	//TopDownCameraComponent->SetActive(false);
	/*
	playerController->SetViewTargetWithBlend(
		this,
		0.5f,
		EViewTargetBlendFunction::VTBlend_Linear,
		0.0f, // 커브지수 기본 0.
		false // true면 카메라전환 도중에 위치갱신 안함
	);
	*/
}
void AConclaveCharacter::SetController_FirstSight()
{
	UE_LOG(LogTemp, Warning, TEXT("First Camera"));
	AConclavePlayerController* playerController;
	playerController = Cast<AConclavePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->ChangeSightType(EPlayerSightType::FirstSight);

	ThirdCameraComponent->SetActive(false);
	if (FirstCameraComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("First Camera Null"));
	}
	else
	{
		FirstCameraComponent->SetActive(true);
	}

	// InputMode 설정
	FInputModeGameOnly InputModeData;
	playerController->SetInputMode(InputModeData);
	playerController->bShowMouseCursor = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction

	GetMesh()->SetVisibility(false);



	// 자기만 안보이게 하는 방법 있었는뎀.. 기억안낭
}
void AConclaveCharacter::SetController_TopDown()
{
	UE_LOG(LogTemp, Warning, TEXT("TopDown Camera"));

	AConclavePlayerController* playerController;
	playerController = Cast<AConclavePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->ChangeSightType(EPlayerSightType::TopDown);

	// InputMode 설정
	FInputModeGameAndUI InputModeData;
	playerController->SetInputMode(InputModeData);
	playerController->bShowMouseCursor = true;

	ThirdCameraComponent->SetActive(false);
	TopDownCameraComponent->SetActive(true);
}



void AConclaveCharacter::CharacterInteract()
{
	if (Inventory == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("inventory null"));
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("TryInteract"));
	Inventory->Interfact();
}


void AConclaveCharacter::TryAttack()
{
	AnimInstance->ChangeCharacterAnimState(ECharacterAnimState::MeleeAttack);
}


void AConclaveCharacter::ResetAnimState()
{
	AnimInstance->OnStateAnimationEnds(ECharacterAnimState::MeleeAttack);
}

void AConclaveCharacter::InitTopDownCamera()
{
	// Create a camera boom...
	TopDownSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TopDownSpringArm"));
	TopDownSpringArm->SetupAttachment(RootComponent);
	TopDownSpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	TopDownSpringArm->TargetArmLength = 800.f;
	TopDownSpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	TopDownSpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level


	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(TopDownSpringArm, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AConclaveCharacter::InitThirdCamera()
{
	ThirdSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdSpringArm"));
	ThirdSpringArm->SetupAttachment(RootComponent);
	ThirdSpringArm->TargetArmLength = 400.0f;
	ThirdSpringArm->bUsePawnControlRotation = true;
		 
	ThirdCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCameraComponent->SetupAttachment(ThirdSpringArm, USpringArmComponent::SocketName);
	ThirdCameraComponent->bUsePawnControlRotation = false;


}

void AConclaveCharacter::InitFirstCamera()
{
	// Create a CameraComponent	
	FirstCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstCameraComponent->SetRelativeLocation(FVector(30.f, 0.f, 60.f)); // Position the camera
	FirstCameraComponent->bUsePawnControlRotation = true;
}
