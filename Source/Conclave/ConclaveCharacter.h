// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ConclaveCharacter.generated.h"

#define DEFAULT_SETTING UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))

class UInventory;
class UCameraComponent;
class USpringArmComponent;
//class AThirdCameraActor;
//class AFirstCameraActor;
UCLASS(Blueprintable)
class AConclaveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AConclaveCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	// TopDown
	FORCEINLINE  UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE  USpringArmComponent* GetCameraBoom() const { return TopDownSpringArm; }


	// Third
	FORCEINLINE  UCameraComponent* GetThirdCameraComponent() const { return ThirdCameraComponent; }
	FORCEINLINE  USpringArmComponent* GetThirdSpringArm() const { return ThirdSpringArm; }

	// First
	FORCEINLINE  UCameraComponent* GetFirstCameraComponent()  { return FirstCameraComponent; }


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	 UCameraComponent* TopDownCameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	 USpringArmComponent* TopDownSpringArm;



	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	 UCameraComponent* ThirdCameraComponent;
	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ThirdSpringArm;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstCameraComponent;

public:
	UFUNCTION(BlueprintCallable)
	void SetController_ThirdSight();

	UFUNCTION(BlueprintCallable)
	void SetController_TopDown();

	UFUNCTION(BlueprintCallable)
	void SetController_FirstSight();

	// 블루프린트에서 정의할겨
	UFUNCTION(BlueprintImplementableEvent, Category = "Item")
	void AddItemToWidget(FItemData ItemData);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInventory> Inventory;

	UFUNCTION()
	void CharacterInteract();
private:
	//FItemData Inventory_AddItem();

	void InitTopDownCamera();
	void InitThirdCamera();
	void InitFirstCamera();
};

