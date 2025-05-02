// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyWidget.h"

#include "LobbyMenu.generated.h"


class UButton;
class UWidget;
class UEditableTextBox; // 호스트 이름 입력하기
class UPanelWidget;
class UWidgetSwitcher; // WidgetSwitcher로 위젯 왔다갔다함

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayer;
	uint16 MaxPlyer;
	FString HostUserName;
};

/**
 * 
 */
UCLASS()
class CONCLAVE_API ULobbyMenu : public ULobbyWidget
{
	GENERATED_BODY()
public:
	ULobbyMenu(const FObjectInitializer& ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);

	void SelectIndex(uint32 Index);
	
protected:
	virtual bool Initialize(); // 가상함수 초기화
private:
	// [호스트 바인딩]
	// 호스트 메뉴 활성화 : HostMenuButton
	// 호스트 생성 버튼 : ConfirmHostButton
	// [조인바인딩]
	// 조인 메뉴 활성화 : JoinMenuButton
	// 조인으로 접속 ConfirmJoinButton
	// [돌아가기]
	// Host->Menu : CancelHostButton
	// Join->Menu : CancelJoinButton

	// [위젯 바인딩]
	// 메인 : MainMenu
	// 호스트 : HostMenu
	// 조인 : JoinMenu

	// [위젯 스위쳐]
	// UWidgetSwitcher* WidgetSwitcher;

	// [호스트 - 서버 이름 입력창]
	// UEditableTextBox* ServerHostName

	// [ServerRow 생성공간]
	// UPanelWidget* ServerList;


	// ServerRow 클래스 등록해줘야함
	TSubclassOf<class UUserWidget> ServerRowClass;

	// 버튼
	UPROPERTY(meta = (BindWidget))
	UButton* HostMenuButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmHostButton;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinMenuButton;
	UPROPERTY(meta = (BindWidget))
	UButton* ConfirmJoinButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CancelHostButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CancelJoinButton;


	// 위젯
	UPROPERTY(meta = (BindWidget))
	 UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
	 UWidget* HostMenu;
	UPROPERTY(meta = (BindWidget))
	 UWidget* JoinMenu;



	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;


	// 호스트창에서 서버 이름
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ServerHostName;


	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ServerList;




	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenHostMenu();

	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OpenDefaultMenu();

	UFUNCTION()
	void QuitPressed();

	

	TOptional<uint32> SelectedIndex; // 선택된 서버 번호를 넘김

	void UpdateChildren();
};
