// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

		virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> MenuWidgetClass;

	UPROPERTY(EditAnywhere)
		class UUW_MainMenu* MenuWidget;

	UPROPERTY(EditAnywhere)
		class UGI_PlayerInfo* PlayerInfo;

	void EnableMouse();

public:

	void LaunchGame(FString Name, int MapIndex);

	UPROPERTY(EditAnywhere)
		TArray<class UMapDataAsset*> MapAssets;

	UPROPERTY(EditAnywhere)
		FString GameLevelName;

	UPROPERTY(EditAnywhere)
		FString MainMenuName;


};
