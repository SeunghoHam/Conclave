// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_PlayerAttackStart.h"
#include "ConclaveCharacter.h"
#include "GameFramework/Actor.h" // When Actor to Chracter Cast use

void UAN_PlayerAttackStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (AConclaveCharacter* MyCharacter = Cast<AConclaveCharacter>(Owner))
		{
			MyCharacter->TriggerAttackStart();
		}
	}
}