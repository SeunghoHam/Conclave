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
	class UTextBlock* ServerName; // ȣ��Ʈ�� ������ ����������

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HostUser; // �������� ������

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConnectionFraction; // ���� �������� �ο� �� �ִ��ο��� �׷��� ������

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false; // ���� 

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
