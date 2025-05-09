// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


class USkeletalMeshComponent;
class UPickUpComponent;
UCLASS()
class CONCLAVE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// 연결
	UFUNCTION(BlueprintImplementableEvent)
	void AttachToCharacter();

	// 해제
	UFUNCTION(BlueprintImplementableEvent)
	void DettachToCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Weapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPickUpComponent* PickupComponent;

	


	UFUNCTION()
	USkeletalMeshComponent* GetWeaponSM() { return Weapon; }
	
	UFUNCTION()
	void WeaponEnable(AConclaveCharacter* _character);

	UFUNCTION()
	void WeaponDisable(AConclaveCharacter* _character);

private:
	void WeaponInit();
};
