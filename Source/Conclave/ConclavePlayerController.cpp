// Copyright Epic Games, Inc. All Rights Reserved.

#include "ConclavePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "ConclaveCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "UObject/ConstructorHelpers.h"
#include "ConclaveCharacter.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AConclavePlayerController::AConclavePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//Character = Cast<AConclaveCharacter>(GetCharacter());
}

void AConclavePlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	SightType = EPlayerSightType::ThirdSight;

	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
	bShowMouseCursor = false;
}


void AConclavePlayerController::ChangeSightType(EPlayerSightType _type)
{
	SightType = _type;
}

void AConclavePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Player, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AConclavePlayerController::OnMove);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AConclavePlayerController::OnInteract);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AConclavePlayerController::OnLook);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AConclavePlayerController:: OnAttack);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AConclavePlayerController::OnMove(const FInputActionValue& Value)
{
	if (SightType == EPlayerSightType::TopDown)
	{
		//UE_LOG(LogTemp, Display, TEXT("TopDown Movement"));
		FVector2D MovementVector = Value.Get<FVector2D>();

		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
		GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
	}
	else if (SightType == EPlayerSightType::ThirdSight)
	{
		//UE_LOG(LogTemp, Display, TEXT("ThirdSight Movement"));
		FVector2D MovementVector = Value.Get<FVector2D>();


			// find out which way is forward
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement 
			GetCharacter()->AddMovementInput(ForwardDirection, MovementVector.Y);
			GetCharacter()->AddMovementInput(RightDirection, MovementVector.X);
	}
	else if (SightType == EPlayerSightType::FirstSight)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		//GetCharacter()->AddMovementInput(Cast<AConclaveCharacter>(GetCharacter())->GetForwardVector(), MovementVector.Y);
		//GetCharacter()->AddMovementInput(Cast<AConclaveCharacter>(GetCharacter())->GetRightVector(), MovementVector.X);
		GetCharacter()->AddMovementInput(GetCharacter()->GetActorForwardVector(), MovementVector.Y);
		GetCharacter()->AddMovementInput(GetCharacter()->GetActorRightVector(), MovementVector.X);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("nanimo nakat ta!"));
	}

}

void AConclavePlayerController::OnInteract()
{
	//AConclaveCharacter* cha = Cast<AConclaveCharacter>(GetCharacter());
	Cast<AConclaveCharacter>(GetCharacter())->CharacterInteract();
	//cha->CharacterInteract();
}

void AConclavePlayerController::OnLook(const FInputActionValue& Value)
{
	// input is a Vector2D'
	if (SightType == EPlayerSightType::TopDown) return;

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	//UE_LOG(LogTemp, Warning, TEXT("Value x : %f,Value y : %f"), LookAxisVector.X, LookAxisVector.Y);

		// add yaw and pitch input to controller
	GetCharacter()->AddControllerYawInput(LookAxisVector.X);
	GetCharacter()->AddControllerPitchInput(LookAxisVector.Y);
	
}

void AConclavePlayerController::OnAttack()
{
	UE_LOG(LogTemp, Display, TEXT("OnAttack"));
	Cast<AConclaveCharacter>(GetCharacter())->SetAttack(true);
}
