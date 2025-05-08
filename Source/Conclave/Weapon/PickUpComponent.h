// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ConclaveCharacter.h"
#include "PickUpComponent.generated.h"

/**
 * 
 */
//class AConclaveCharacter;
class AWeaponBase;

// (type, parameter)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPickUp, AConclaveCharacter*, character); // 픽업 델리게이트 호출

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CONCLAVE_API UPickUpComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UPickUpComponent();

	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FPickUp OnPickUp;

	void SetDelegateFunction(); // WeaponBase에서 호출시킬거 그럴필요있나?

private:
	UFUNCTION()
	void Attach();

protected:
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

private:
	AWeaponBase* WeaponBase;
};
