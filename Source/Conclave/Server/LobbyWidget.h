// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "LobbyInterface.h"

#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONCLAVE_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// UI  상태로 게임상태 적용시키기
	void Setup();
	// 게임상태로 돌아가는건데 명칭 바꾸는게 좋을듯
	void TearDown();

	void SetLobbyInterface(ILobbyInterface* _LobbyInterface);
protected:

	ILobbyInterface* LobbyInterface;

};
