// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECharacterAnimState: uint8 // : uint8 과 같이 8비트라는것을 명시할 수 있음
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
	ECharacterAnimState AnimState; // ABP에서 모션정함


	// 애니메이션에따라 종료로 연결되는 모션이 다르도록 설정 의미있나? 모르겠다
	UFUNCTION(BlueprintCallable)
	void OnStateAnimationEnds(const ECharacterAnimState& state);


	void ChangeCharacterAnimState(const ECharacterAnimState& state);
};
