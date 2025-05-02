// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "Components/Button.h"

#include "LobbyMenu.h" // Parent ���

void UServerRow::Setup(ULobbyMenu* _Parent, uint32 _Index)
{
	this->Parent = _Parent;
	Index = _Index;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	//  LobbyMenu �� �ε�����ȣ�� ���� ������ �ε��������� �����Ŵ
	Parent->SelectIndex(Index); // 
}
