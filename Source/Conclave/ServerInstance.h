// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Server/LobbyInterface.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "ServerInstance.generated.h"

/**
 * 
 */

class ULobbyMenu;
UCLASS()
class CONCLAVE_API UServerInstance : public UGameInstance, public ILobbyInterface
{
	GENERATED_BODY()
public:
	//UServerInstance(const FObjectInitializer& ObjectInitializer); // �ν��Ͻ� ã�ƿ���
	UServerInstance();

	virtual void Init();


	// LevelBP���� �����ų��?
	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu(); // �ΰ��� UI�̱⿡ ������ �Ⱦ�


	// LobbyInteface���� ���� �Լ���
	UFUNCTION(Exec)
	void Host(FString ServerName) override;

	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	void StartSession();

	virtual void LoadMainMenu() override;

	void RefreshServerList() override;

	UPROPERTY(BlueprintReadOnly)
	FString TravelLocation = "/Game/Maps/TopDonwMap";

private:
	void CreateSession();

	TSubclassOf<class UUserWidget> LobbyClass; // ConstructorHelper�� �νĽ�Ű�� �غ���
	//TSubclassOf<class UUserWidget> InGameMenuClass;

	ULobbyMenu* Lobby;

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionsComplete(bool Success);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);

	FString DesiredServerName;

};
