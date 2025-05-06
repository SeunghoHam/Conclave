// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdCameraActor.generated.h"
class UCameraComponent;
UCLASS()
class CONCLAVE_API AThirdCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdCameraActor();


	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return ThirdCamera; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCameraComponent* ThirdCamera;

};
