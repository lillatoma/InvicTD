// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvicEnemySpawner.generated.h"

UCLASS()
class INVICTD_API AInvicEnemySpawner : public AActor
{
	GENERATED_BODY()
	


public:	
	// Sets default values for this actor's properties
	AInvicEnemySpawner();

	virtual void SpawnEnemy();

	virtual void SetEnemiesLeftToSpawn(int count);
	//This function counts enemies on the map + enemies left to spawn
	virtual int CountEnemiesLeft() const;
	
	virtual void SetConvertedPath(TArray<FVector> Path);

	virtual void SetEnemySpawnTime(float time);

	virtual TArray<class AInvicEnemy*> GetEnemyList() const;

	virtual void RemoveEnemyFromList(class AInvicEnemy* Enemy);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> EnemyActor;

	TArray<FVector> ConvertedPath;

	TArray<class AInvicEnemy*> EnemiesOnMap;

	int EnemiesLeftToSpawn;
	float SpawnTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
