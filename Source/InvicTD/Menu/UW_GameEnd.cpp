// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_GameEnd.h"
#include "InvicTD\Game\InvicGameModeBase.h"

void UUW_GameEnd::OnButtonClick()
{
	AInvicGameModeBase* GameMode = Cast<AInvicGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->ActOnGameEnd();
}
