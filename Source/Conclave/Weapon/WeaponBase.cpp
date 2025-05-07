// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "PickUpComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "PickUpComponent.h"
// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	RootComponent = Weapon;

	PickupComponent = CreateDefaultSubobject<UPickUpComponent>(TEXT("PickUpComponent"));
	PickupComponent->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::WeaponEnable(AConclaveCharacter* _character)
{

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(_character->GetMesh(), AttachmentRules, TEXT("GripPoint"));

	Weapon->SetSimulatePhysics(false);
	Weapon->SetEnableGravity(false);
}

void AWeaponBase::WeaponDisable(AConclaveCharacter* _character)
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
}

