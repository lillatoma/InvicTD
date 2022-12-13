// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicGameModeBase.h"
#include "InvicTD\Map\InvicMapBuilder.h"
#include "InvicTD\Map\MapDataAsset.h"
#include "InvicTD\Menu\GI_PlayerInfo.h"
#include "InvicTD\Menu\UW_Game.h"
#include "InvicTD\Menu\UW_GameEnd.h"
#include "InvicEnemySpawner.h"
#include "InvicPlayer.h"


#include "Kismet/GameplayStatics.h"

void AInvicGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Info = Cast<UGI_PlayerInfo>(GetGameInstance());

	if (Info)
		Info->StatsAsset = StatsAsset;
	
	SpawnMapGenerator();
	SpawnEnemySpawner();
	SpawnPlayer();
	





	SpawnTextWidget();


	
}

void AInvicGameModeBase::SpawnEndWidget()
{
	if (EndWidgetClass)
	{
		EndWidget = Cast<UUW_GameEnd>(CreateWidget(GetWorld(), EndWidgetClass));

		if (EndWidget)
		{
			EndWidget->AddToViewport();
			EndWidget->SetWinloseText(bCurrentMatchWon);
		}
	}
}

void AInvicGameModeBase::SpawnTextWidget()
{
	if (TextWidgetClass)
	{
		TextWidget = Cast<UUW_Game>(CreateWidget(GetWorld(), TextWidgetClass));

		if (TextWidget && Info)
		{
			TextWidget->AddToViewport();
			TextWidget->SetThePlayerName(Info->PlayerName);
			TextWidget->SetTextFormat("Name: {0}\nLevel: {1}\nEnemies Killed: {2}\nEnemies Left: {3}");
			UpdateWidgetText();
		}
	}
}

void AInvicGameModeBase::SpawnMapGenerator()
{
	FTransform SpawnTransform(FRotator(), FVector(), FVector(1, 1, 1));
	AInvicMapBuilder* MapGen = Cast<AInvicMapBuilder>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, MapGenerator, SpawnTransform));

	if (MapGen)
	{
		if (Info && Info->CurrentLevel < Info->MapAssets.Num())
			MapGen->SetMapAsset(Info->MapAssets[Info->CurrentLevel]);
		MapBuilderOnMap = Cast<AInvicMapBuilder>(UGameplayStatics::FinishSpawningActor(MapGen, SpawnTransform));
	}
}

void AInvicGameModeBase::SpawnEnemySpawner()
{
	FTransform SpawnTransform(FRotator(), FVector(), FVector(1, 1, 1));
	AInvicEnemySpawner* EnemySpawn = Cast<AInvicEnemySpawner>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, EnemySpawner, SpawnTransform));

	if (EnemySpawn && MapBuilderOnMap)
	{
		PassPathToSpawner(EnemySpawn, MapBuilderOnMap);
		EnemySpawn->SetEnemiesLeftToSpawn(MapBuilderOnMap->GetAsset()->GetEnemyCount());
		EnemySpawn->SetEnemySpawnTime(MapBuilderOnMap->GetAsset()->GetSpawnGap());
		EnemySpawn->Stats = this->StatsAsset;
		EnemySpawnerOnMap = Cast< AInvicEnemySpawner>(UGameplayStatics::FinishSpawningActor(EnemySpawn, SpawnTransform));
	}
}

void AInvicGameModeBase::SpawnPlayer()
{

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

void AInvicGameModeBase::OnEnemyKilled()
{
	EnemiesKilled++;

	UpdateWidgetText();
}

void AInvicGameModeBase::UpdateWidgetText()
{
	if (TextWidget && Info && EnemySpawnerOnMap)
	{
		TextWidget->SetTheText(Info->CurrentLevel + 1, EnemiesKilled, EnemySpawnerOnMap->CountEnemiesLeft());
	}
}

void AInvicGameModeBase::PreloseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	bCurrentMatchEnded = true;
	bCurrentMatchWon = false;
	SpawnEndWidget();
}

void AInvicGameModeBase::LoseGame()
{
	if (Info)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*Info->MainMenuLevelName));
	}
}

void AInvicGameModeBase::PrewinGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	bCurrentMatchEnded = true;
	bCurrentMatchWon = true;
	SpawnEndWidget();

}

void AInvicGameModeBase::WinGame()
{
	if (Info)
	{
		Info->CurrentLevel++;
		if (Info->CurrentLevel >= Info->MapAssets.Num())
			Info->CurrentLevel = 0;
		UGameplayStatics::OpenLevel(GetWorld(), FName(*Info->GameLevelName));
	}
}

void AInvicGameModeBase::ActOnGameEnd()
{
	if (bCurrentMatchEnded)
	{
		if (bCurrentMatchWon)
			WinGame();
		else LoseGame();
	}
}
