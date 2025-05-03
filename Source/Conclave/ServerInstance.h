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
	//UServerInstance(const FObjectInitializer& ObjectInitializer); // 인스턴스 찾아오기
	UServerInstance();

	virtual void Init();


	// LevelBP에서 실행시킬거?
	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu(); // 인게임 UI이기에 당장은 안씀


	// LobbyInteface에서 받을 함수들
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

	TSubclassOf<class UUserWidget> LobbyClass; // ConstructorHelper로 인식시키기 해보기
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
