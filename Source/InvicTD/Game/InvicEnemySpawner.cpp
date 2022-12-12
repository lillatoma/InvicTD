// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicEnemySpawner.h"

#include "InvicEnemy.h"
#include "StatsDataAsset.h"

#include "Kismet/GameplayStatics.h"
// Sets default values
AInvicEnemySpawner::AInvicEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInvicEnemySpawner::SpawnEnemy()
{
	if (EnemiesLeftToSpawn <= 0)
		return;
	FTransform SpawnTransform(FRotator(), ConvertedPath[0], FVector(1, 1, 1));
	AInvicEnemy* EnemySpawned = Cast<AInvicEnemy>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, EnemyActor, SpawnTransform));
	AInvicEnemy* RealEnemy = nullptr;
	if (EnemySpawned)
	{
		EnemySpawned->Path = ConvertedPath;
		EnemySpawned->Spawner = this;
		if(Stats)
			EnemySpawned->HealthMultiplier = Stats->GetEnemyHealth();
		RealEnemy = Cast<AInvicEnemy>(UGameplayStatics::FinishSpawningActor(EnemySpawned, SpawnTransform));
		EnemiesLeftToSpawn--;
	}

	if (RealEnemy)
		EnemiesOnMap.Add(RealEnemy); 
}

void AInvicEnemySpawner::SetEnemiesLeftToSpawn(int count)
{
	EnemiesLeftToSpawn = count;
}

int AInvicEnemySpawner::CountEnemiesLeft() const
{
	return EnemiesLeftToSpawn + EnemiesOnMap.Num();
}

void AInvicEnemySpawner::SetConvertedPath(TArray<FVector> Path)
{
	ConvertedPath = Path;
}

void AInvicEnemySpawner::SetEnemySpawnTime(float time)
{
	SpawnTime = time;
}

TArray<class AInvicEnemy*> AInvicEnemySpawner::GetEnemyList() const
{
	return EnemiesOnMap;
}

void AInvicEnemySpawner::RemoveEnemyFromList(AInvicEnemy* Enemy)
{
	EnemiesOnMap.Remove(Enemy);
}

// Called when the game starts or when spawned
void AInvicEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AInvicEnemySpawner::SpawnEnemy, SpawnTime, true, SpawnTime);
}

// Called every frame
void AInvicEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

