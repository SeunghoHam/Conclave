// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Actor/ItemBase.h"

#include "Inventory.generated.h"

class UItemBase;
class APlayerController;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONCLAVE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AttachCharacter(class AConclaveCharacter* _character);

	UFUNCTION(BlueprintImplementableEvent, Category = "Item")
	void AddItemToWidget(FItemData ItemData);

	UFUNCTION()
	void Interfact();
private:
	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	//void UseItem(TSubclassOf<UItemBase> ItemSubClass);
	
	UPROPERTY()
	TObjectPtr<AConclaveCharacter> Owner;


	//TObjectPtr<APlayerController> PC;
	FVector Start;
	FVector End;
};
