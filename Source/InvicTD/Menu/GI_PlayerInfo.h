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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int CurrentLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<class UMapDataAsset*> MapAssets;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString MainMenuLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString GameLevelName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAudioComponent* Audio;


	UFUNCTION(BlueprintCallable)
		void StartPlayingSound(class USoundBase* Sound);

};