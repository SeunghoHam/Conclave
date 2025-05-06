// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/FirstCameraActor.h"
//#include "Camera/CameraComponent.h"

// Sets default values
AFirstCameraActor::AFirstCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFirstCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

