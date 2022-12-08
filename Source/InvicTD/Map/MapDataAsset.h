// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InvicMapBuilder.h"

#include "MapDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UMapDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FIntPoint GetSize() const;
	void SetSize(FIntPoint size);

	EMB_TileType GetTile(FIntPoint point) const;
	void SetTile(FIntPoint point, EMB_TileType Tile);

	int GetEnemyCount() const;
	void SetEnemyCount(int enemyCount);

	float GetSpawnGap() const;
	void SetSpawnGap(float spawnGap);

	FIntPoint GetPathPoint(int index) const;
	void AddPathPoint(FIntPoint pathPoint);
	void SetPathPoint(int index, FIntPoint pathPoint);

	TArray<FIntPoint>* GetPath();

private:
	UPROPERTY(EditAnywhere)
		FIntPoint Size;

	UPROPERTY(EditAnywhere)
		TArray<EMB_TileType> Tiles;
	
	UPROPERTY(EditAnywhere)
		int TotalEnemyCount;

	UPROPERTY(EditAnywhere)
		float SpawnGap;

	UPROPERTY(EditAnywhere)
		TArray<FIntPoint> Path;

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> PathObject;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> HighObject;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AActor>> PathScenery;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AActor>> HighScenery;
};
