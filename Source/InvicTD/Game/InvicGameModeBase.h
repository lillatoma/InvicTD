// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvicGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API AInvicGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> TextWidgetClass;

	UPROPERTY(EditAnywhere)
		class UUW_Game* TextWidget;

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> EndWidgetClass;

	UPROPERTY(EditAnywhere)
		class UUW_GameEnd* EndWidget;

	UPROPERTY(VisibleAnywhere)
		class UGI_PlayerInfo* Info;

	UPROPERTY(VisibleAnywhere)
		class AInvicEnemySpawner* EnemySpawnerOnMap;

	bool bCurrentMatchEnded = false;
	bool bCurrentMatchWon = false;

protected:
	virtual void BeginPlay() override;

	virtual void SpawnEndWidget();
	virtual void SpawnTextWidget();


	UPROPERTY(EditAnywhere, Category = "Map Builder")
		TSubclassOf<class AInvicMapBuilder> MapGenerator;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
		TSubclassOf<class AInvicEnemySpawner> EnemySpawner;

	UPROPERTY(EditAnywhere, Category = "Player")
		TSubclassOf<class AInvicPlayer> PlayerToSpawn;

	UPROPERTY(EditAnywhere, Category = "Player")
		FVector PlayerSpawnPosition = FVector(-250.0f,0.0f,1000.0f);

	virtual void PassPathToSpawner(class AInvicEnemySpawner* Spawner, class AInvicMapBuilder* Map);


	int EnemiesKilled = 0;

public:

	void OnEnemyKilled();

	void UpdateWidgetText();

	void PreloseGame();

	void LoseGame();

	void PrewinGame();

	void WinGame();

	void ActOnGameEnd();
};
