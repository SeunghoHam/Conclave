// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

void ULobbyWidget::Setup()
{	
	UE_LOG(LogTemp, Display, TEXT("LobbyWidget -Setup"));
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}

void ULobbyWidget::TearDown()
{
	UE_LOG(LogTemp, Display, TEXT("LobbyWidget - TearDown"));
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	// 입력모드 변경하기
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
}

void ULobbyWidget::SetLobbyInterface(ILobbyInterface* _lobbyInterface)
{
	UE_LOG(LogTemp, Display, TEXT("SetLobbyInterface"));
	this->LobbyInterface = _lobbyInterface;
}
