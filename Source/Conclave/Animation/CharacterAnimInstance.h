// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECharacterAnimState: uint8 // : uint8 �� ���� 8��Ʈ��°��� ����� �� ����
{
	Locotmotion = 0,
	MeleeAttack,
	Hit,
	Die
};

UCLASS()
class CONCLAVE_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	ECharacterAnimState AnimState; // ABP���� �������


	// �ִϸ��̼ǿ����� ����� ����Ǵ� ����� �ٸ����� ���� �ǹ��ֳ�? �𸣰ڴ�
	UFUNCTION(BlueprintCallable)
	void OnStateAnimationEnds(const ECharacterAnimState& state);


	void ChangeCharacterAnimState(const ECharacterAnimState& state);
};
