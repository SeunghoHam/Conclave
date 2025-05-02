// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UButton;
class ULobbyMenu;
/**
 * 
 */
UCLASS()
class CONCLAVE_API UServerRow : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName; // 호스트가 설정한 서버명으로

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostUser; // 유저네임 가져옴

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConnectionFraction; // 현재 접속중인 인원 및 최대인원수 그런거 적을거

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false; // 현재 

	void Setup(ULobbyMenu* _Parent, uint32 _Index);


private:
	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;

	UPROPERTY()
	ULobbyMenu* Parent;

	uint32 Index;

	UFUNCTION()
	void OnClicked();
};
