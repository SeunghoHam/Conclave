// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"
#include "Components/Button.h"

#include "LobbyMenu.h" // Parent 사용

void UServerRow::Setup(ULobbyMenu* _Parent, uint32 _Index)
{
	this->Parent = _Parent;
	Index = _Index;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	//  LobbyMenu 의 인덱스번호를 눌린 서버의 인덱스값으로 변경시킴
	Parent->SelectIndex(Index); // 
}
