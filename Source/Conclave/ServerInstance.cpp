// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
//#include "OnlineSessionNames.h" // SEARCH_PRESENCE 포함되어있음?

#include "Server/LobbyMenu.h"
#include "Server/LobbyWidget.h"

#define SEARCH_PRESENCE FName(TEXT("presence"))

const static FName SESSION_NAME = TEXT("Game"); // 스팀에서 인식하는 세션명
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName"); // 스팀 세션에서 인식하는 키값

//UServerInstance::UServerInstance(const FObjectInitializer& ObjectInitializer)
UServerInstance::UServerInstance()
{
	// 생성자에서 WBP 로비 개체 활성화 시키기
	ConstructorHelpers::FClassFinder<UUserWidget> LobbyBPClass(TEXT("/Game/Menu/WBP_Lobby"));
	if (!ensure(LobbyBPClass.Class != nullptr)) return;

	LobbyClass = LobbyBPClass.Class;
	/*
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;

	InGameMenuClass = InGameMenuBPClass.Class;
	*/
}

void UServerInstance::Init()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UServerInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UServerInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UServerInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UServerInstance::OnJoinSessionComplete);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}

	if (GEngine != nullptr)
	{
		// 네크워크 연결 실패시 동작함
		GEngine->OnNetworkFailure().AddUObject(this, &UServerInstance::OnNetworkFailure);
	}
}

void UServerInstance::LoadMenuWidget()
{
	// 로비위젯이 있다면 설정하기
	if (!ensure(LobbyClass != nullptr)) return;

	Lobby = CreateWidget<ULobbyMenu>(this, LobbyClass);
	if (!ensure(Lobby != nullptr)) return;

	
	Lobby->Setup();

	Lobby->SetLobbyInterface(this);
}

void UServerInstance::InGameLoadMenu()
{
	/*
	if (!ensure(InGameMenuClass != nullptr)) return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);*/
}

void UServerInstance::Host(FString ServerName)
{
	// 입력된 ServerName을 저장하고 cpp 위에 설정한 "Game" 이름으로 세션 생성하기
	DesiredServerName = ServerName;
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UServerInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	if (Lobby!= nullptr)
	{
		Lobby->TearDown();
	}

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UServerInstance::StartSession()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->StartSession(SESSION_NAME); // 세션으로 이동하기
	}
}

void UServerInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	// 네트워크 연결 해제될때도 일로올거임
	PlayerController->ClientTravel("/Game/Maps/Lobby", ETravelType::TRAVEL_Absolute);
}

void UServerInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		//SessionSearch->bIsLanQuery = true;
		SessionSearch->MaxSearchResults = 100;
		//SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UServerInstance::CreateSession()
{
	// 세션명이 "NULL" 이라면 LanMath(스팀연결) 이 아니라 로컬테스트용
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSettings;
		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			SessionSettings.bIsLANMatch = true;
		}
		else
		{
			SessionSettings.bIsLANMatch = false;
		}
		SessionSettings.NumPublicConnections = 4; // 최대 접속 인원수
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, DesiredServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings); // 세션인터페이스에서 세션 생성시킴
	}
}

void UServerInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	// 세션 생성이 완료되면 서버 이동을 시작함
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not create session"));
		return;
	}

	if (Lobby != nullptr)
	{
		Lobby->TearDown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/Lobby?listen");
}

void UServerInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success) {
		CreateSession();
	}
}

void UServerInstance::OnFindSessionsComplete(bool Success)
{
	if (Success && SessionSearch.IsValid() && Lobby != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished Find Session"));

		TArray<FServerData> ServerNames;
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session names: %s"), *SearchResult.GetSessionIdStr());
			FServerData Data;
			Data.MaxPlyer = SearchResult.Session.SessionSettings.NumPublicConnections;
			Data.CurrentPlayer = Data.MaxPlyer - SearchResult.Session.NumOpenPublicConnections; // 현재 플레이 = 최대 - 참여가능수
			Data.HostUserName = SearchResult.Session.OwningUserName;
			FString ServerName;
			if (SearchResult.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName))
			{
				Data.Name = ServerName;
			}
			else
			{
				Data.Name = "Could not find name.";
			}
			ServerNames.Add(Data);
		}

		Lobby->SetServerList(ServerNames);
	}
}

void UServerInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address)) {
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."));
		return;
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UServerInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	// 네트워크 해제시에는 로비화면으로 이동시킴.
	LoadMainMenu();
}
