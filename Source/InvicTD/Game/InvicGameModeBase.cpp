// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicGameModeBase.h"
#include "InvicTD\Map\InvicMapBuilder.h"
#include "InvicTD\Map\MapDataAsset.h"
#include "InvicEnemySpawner.h"
#include "InvicPlayer.h"

#include "Kismet/GameplayStatics.h"

void AInvicGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//Try spawning the mapgenerator
	AActor* MapGenActor = GetWorld()->SpawnActor<AActor>(MapGenerator, FVector(), FRotator());
	AInvicMapBuilder* MapGen = Cast<AInvicMapBuilder>(MapGenActor);
	
	FTransform SpawnTransform(FRotator(),FVector(), FVector(1, 1, 1));
	AInvicEnemySpawner* EnemySpawn = Cast<AInvicEnemySpawner>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, EnemySpawner, SpawnTransform));

	if (EnemySpawn)
	{
		PassPathToSpawner(EnemySpawn, MapGen);
		EnemySpawn->SetEnemiesLeftToSpawn(MapGen->GetAsset()->GetEnemyCount());
		EnemySpawn->SetEnemySpawnTime(MapGen->GetAsset()->GetSpawnGap());
		UGameplayStatics::FinishSpawningActor(EnemySpawn, SpawnTransform);
	}

	AActor* PlayerActor = GetWorld()->SpawnActor<AActor>(PlayerToSpawn, PlayerSpawnPosition, FRotator());
	AInvicPlayer* Player = Cast<AInvicPlayer>(PlayerActor);
	
}

void AInvicGameModeBase::PassPathToSpawner(AInvicEnemySpawner* Spawner, AInvicMapBuilder* Map)
{
	TArray<FVector> ConvertedPath;
	UMapDataAsset* MapAsset = Map->GetAsset();
	TArray<FIntPoint> Path = *MapAsset->GetPath();
	for (int i = 0; i < Path.Num(); i++)
	{
		ConvertedPath.Add(Map->ConvertGridToWorld(Path[i]));
	}
	Spawner->SetConvertedPath(ConvertedPath);
}
