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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Map Builder")
		TSubclassOf<class AInvicMapBuilder> MapGenerator;

	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
		TSubclassOf<class AInvicEnemySpawner> EnemySpawner;

	UPROPERTY(EditAnywhere, Category = "Player")
		TSubclassOf<class AInvicPlayer> PlayerToSpawn;

	UPROPERTY(EditAnywhere, Category = "Player")
		FVector PlayerSpawnPosition = FVector(-250.0f,0.0f,1000.0f);

	virtual void PassPathToSpawner(class AInvicEnemySpawner* Spawner, class AInvicMapBuilder* Map);

public:
	void PreloseGame();

	void LoseGame();

	void PrewinGame();

	void WinGame();
};
