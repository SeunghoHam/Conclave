// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstCameraActor.generated.h"

class UCameraComponent;
UCLASS()
class CONCLAVE_API AFirstCameraActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstCameraActor();
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return FirstCamera; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCameraComponent* FirstCamera;
};
