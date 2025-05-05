// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMenu.h"

#include "UObject/ConstructorHelpers.h" // 에디터 검색

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

ULobbyMenu::ULobbyMenu(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/Menu/WBP_ServerRow"));
	if (!ensure(ServerRowBPClass.Class != nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("ServerRow Bluepirnt is Not Connecting"));
		return;
	}

	ServerRowClass = ServerRowBPClass.Class;
}

void ULobbyMenu::SetServerList(TArray<FServerData> ServerNames)
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FServerData& ServerData : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(ServerData.Name));
		Row->HostUser->SetText(FText::FromString(ServerData.HostUserName));
		FString FractionText = FString::Printf(TEXT("%d/%d"), ServerData.CurrentPlayer, ServerData.MaxPlyer);
		Row->ConnectionFraction->SetText(FText::FromString(FractionText));
		Row->Setup(this, i);
		++i;

		ServerList->AddChild(Row);
	}
}

void ULobbyMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}


bool ULobbyMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (HostMenuButton != nullptr)
		HostMenuButton->OnClicked.AddDynamic(this, &ULobbyMenu::OpenHostMenu);

	if (JoinMenuButton != nullptr)
		JoinMenuButton->OnClicked.AddDynamic(this, &ULobbyMenu::OpenJoinMenu);

	if (ConfirmHostButton != nullptr)
		ConfirmHostButton->OnClicked.AddDynamic(this, &ULobbyMenu::HostServer);

	if (ConfirmJoinButton != nullptr)
		ConfirmJoinButton->OnClicked.AddDynamic(this, &ULobbyMenu::JoinServer);

	if (CancelHostButton != nullptr)
		CancelHostButton->OnClicked.AddDynamic(this, &ULobbyMenu::OpenDefaultMenu);

	if (CancelJoinButton != nullptr)
		CancelJoinButton->OnClicked.AddDynamic(this, &ULobbyMenu::OpenDefaultMenu);

	return true;
}

// 서버 활성화는 인터페이스에서
void ULobbyMenu::HostServer()
{
	UE_LOG(LogTemp, Warning, TEXT("HostServer"));
	if (LobbyInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lobby Interface Null"));
		return;
	}	


	UE_LOG(LogTemp, Warning, TEXT("LobbyMenu::HoserServer"));
	FString ServerName = ServerHostName->Text.ToString();
	LobbyInterface->Host(ServerName);
}

void ULobbyMenu::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("JoinServer"));
	// 선택된 인덱스(서버 번호) 가 있어야 접속되게
	if (SelectedIndex.IsSet() && LobbyInterface != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d."), SelectedIndex.GetValue());
		LobbyInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set."));
	}
}

void ULobbyMenu::OpenHostMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenHostMenu"));
	if (WidgetSwitcher == nullptr) return;
	WidgetSwitcher->SetActiveWidget(HostMenu);
}

void ULobbyMenu::OpenJoinMenu()
{
	UE_LOG(LogTemp, Display, TEXT("TryOpenJoinMenu"));
	if (WidgetSwitcher == nullptr) return;
	//if (LobbyInterface == nullptr) return;
	WidgetSwitcher->SetActiveWidget(JoinMenuButton);
	if (LobbyInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" 'OpenJoniMenu::LobbyInteface = null"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT(" RefreshServerList"));

	LobbyInterface->RefreshServerList();
}


// 기본창으로 변경
void ULobbyMenu::OpenDefaultMenu()
{
	if (WidgetSwitcher == nullptr) return;
	if (MainMenu == nullptr) return;
	WidgetSwitcher->SetActiveWidget(MainMenu);
}

void ULobbyMenu::QuitPressed()
{
	// 종료버튼?

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit"); // 커맨드창에 입력되는 효과
}

void ULobbyMenu::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); ++i)
	{
		auto Row = Cast<UServerRow>(ServerList->GetChildAt(i));
		if (Row != nullptr)
		{
			Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}