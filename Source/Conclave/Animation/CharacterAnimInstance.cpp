// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterAnimInstance.h"

void UCharacterAnimInstance::OnStateAnimationEnds(const ECharacterAnimState& state)
{
	//UE_LOG(LogTemp, Display, TEXT("AnimInstance - OnStateAnimtionEnd"));
	if (state != ECharacterAnimState::Locotmotion)
	{
		AnimState = ECharacterAnimState::Locotmotion;
	}
}

void UCharacterAnimInstance::ChangeCharacterAnimState(const ECharacterAnimState& state)
{
	this->AnimState = state;
}
