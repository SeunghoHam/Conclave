// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "ConclaveCharacter.h"

//#include "Actor/ItemBase.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;



	/*
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	PC = World->GetFirstPlayerController();
	*/
	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	//Owner = Cast<ACharacter>(GetOwner());
	// ...
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::AttachCharacter(class AConclaveCharacter* _character)
{
	Owner = _character;
}

/*
void UInventory::AddItemToWidget(FItemData ItemData)
{

}
*/
void UInventory::Interfact()
{
	if (Owner == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Intefact : OwnerCharacter is null"));
		return;
	}
	Start = Owner->GetActorLocation();
	End = Start + Owner->GetActorForwardVector() * 500.0f;

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f);
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	UE_LOG(LogTemp, Warning, TEXT("Min Jun tal"));
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		if (AItemBase* HitActor = Cast<AItemBase>(HitResult.GetActor()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *HitActor->GetName());
			HitActor->ItemInteract(Owner); // ¾×ÅÍ ÆÄ±«½ÃÅ´
		}
	}
}

