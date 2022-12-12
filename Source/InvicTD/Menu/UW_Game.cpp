// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Game.h"

void UUW_Game::SetTextFormat(FString t)
{
	TextFormat = t;
}

void UUW_Game::SetThePlayerName(FString n)
{
	name = n;
}

FString UUW_Game::PutDataIntoFormat(int level, int enemiesKilled, int enemiesLeft)
{
	//const FString Format = TextFormat;
	FString R = FString::Format(*TextFormat, { *name, level, enemiesKilled, enemiesLeft });
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, R);
	return R;
}
