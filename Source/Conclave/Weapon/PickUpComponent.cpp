// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ConclaveCharacter.h"
#include "WeaponBase.h"

UPickUpComponent::UPickUpComponent()
{
	SphereRadius = 32.f;
}

void UPickUpComponent::BeginPlay()
{
	SetDelegateFunction();

	WeaponBase = Cast<AWeaponBase>(GetOwner());
	if(WeaponBase == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Weapon is Null"));
}

void UPickUpComponent::SetDelegateFunction()
{
	OnComponentBeginOverlap.AddDynamic(this,&UPickUpComponent::OnSphereBeginOverlap);
}

void UPickUpComponent::Attach()
{
}

void UPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Display, TEXT("OnSphereBeginOveerlap"));
	AConclaveCharacter* Character = Cast<AConclaveCharacter>(OtherActor);
	if (Character != nullptr)
	{

		UE_LOG(LogTemp, Display, TEXT("Overlap Player"));

		OnPickUp.Broadcast(Character);
		WeaponBase->WeaponEnable(Character);

		OnComponentBeginOverlap.RemoveAll(this);

			/*
		WeaponBase->enable
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		AttachToComponent(Character->GetMesh(), AttachmentRules, TEXT("GripPoint"));
		OnComponentBeginOverlap.RemoveAll(this);

		SetSimulatePhysics(false);
		SetEnableGravity(false);
		*/
	}
}
