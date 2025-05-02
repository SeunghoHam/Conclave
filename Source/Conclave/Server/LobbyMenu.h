// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LobbyWidget.h"

#include "LobbyMenu.generated.h"


class UButton;
class UWidget;
class UEditableTextBox; // ȣ��Ʈ �̸� �Է��ϱ�
class UPanelWidget;
class UWidgetSwitcher; // WidgetSwitcher�� ���� �Դٰ�����

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
	virtual bool Initialize(); // �����Լ� �ʱ�ȭ
private:
	// [ȣ��Ʈ ���ε�]
	// ȣ��Ʈ �޴� Ȱ��ȭ : HostMenuButton
	// ȣ��Ʈ ���� ��ư : ConfirmHostButton
	// [���ι��ε�]
	// ���� �޴� Ȱ��ȭ : JoinMenuButton
	// �������� ���� ConfirmJoinButton
	// [���ư���]
	// Host->Menu : CancelHostButton
	// Join->Menu : CancelJoinButton

	// [���� ���ε�]
	// ���� : MainMenu
	// ȣ��Ʈ : HostMenu
	// ���� : JoinMenu

	// [���� ������]
	// UWidgetSwitcher* WidgetSwitcher;

	// [ȣ��Ʈ - ���� �̸� �Է�â]
	// UEditableTextBox* ServerHostName

	// [ServerRow ��������]
	// UPanelWidget* ServerList;


	// ServerRow Ŭ���� ����������
	TSubclassOf<class UUserWidget> ServerRowClass;

	// ��ư
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


	// ����
	UPROPERTY(meta = (BindWidget))
	 UWidget* MainMenu;
	UPROPERTY(meta = (BindWidget))
	 UWidget* HostMenu;
	UPROPERTY(meta = (BindWidget))
	 UWidget* JoinMenu;



	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;


	// ȣ��Ʈâ���� ���� �̸�
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

	

	TOptional<uint32> SelectedIndex; // ���õ� ���� ��ȣ�� �ѱ�

	void UpdateChildren();
};
