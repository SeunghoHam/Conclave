// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
//#include "InputActionValue.h" // FInputActionValue 등
#include "ConclavePlayerController.generated.h"


UENUM()
enum class EPlayerSightType  : uint8 // uint8 으로 크기 제한해두기
{

	TopDown UMETA(DisplayName = "TopDown"),
	FirstSight UMETA(DisplayName = "FirstSight"),
	ThirdSight UMETA(DisplayName = "ThirdSight")
};
/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AConclavePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AConclavePlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	//UPROPERTY(BlueprintReadOnly)
	 UInputMappingContext* IMC_Player;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	//UPROPERTY(BlueprintReadOnly)

	UInputAction* SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))

	//UPROPERTY(BlueprintReadOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	

	UFUNCTION()
	void ChangeSightType(EPlayerSightType _type);
	

protected:

	//void Move(const FInputActionValue& Value);

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;
	
	// To add mapping context
	virtual void BeginPlay();

private:
	EPlayerSightType SightType;

	//TObjectPtr<AConclaveCharacter> Character;

	void OnMove(const FInputActionValue& Value);
	void OnInteract();


	// ThirdPerson
	/** Called for movement input */
	//void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void OnLook(const FInputActionValue& Value);

	/*
	UFUNCTION()
	void SetFirstSight();

	UFUNCTION()
	void SetTopDown();*/
};


