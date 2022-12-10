// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_PlayerInfo.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UGI_PlayerInfo : public UGameInstance
{
	GENERATED_BODY()
	
public:
	int CurrentLevel;
	FString PlayerName;
	TArray<class UMapDataAsset*> MapAssets;

	FString MainMenuLevelName;
	FString GameLevelName;
};
