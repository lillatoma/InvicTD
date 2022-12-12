// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "GI_PlayerInfo.h"
#include "UW_MainMenu.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGI_PlayerInfo* Info = Cast<UGI_PlayerInfo>(GetGameInstance());
	if (Info)
		PlayerInfo = Info;

	if (MenuWidgetClass)
	{
		MenuWidget = Cast<UUW_MainMenu>(CreateWidget(GetWorld(), MenuWidgetClass));

		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}

	FTimerHandle UnusedHandle;

	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &AMainMenuGameMode::EnableMouse, 0.001f, false);

	//Audio->
	if (PlayerInfo && !PlayerInfo->Audio)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, SoundBase->GetName());
		PlayerInfo->StartPlayingSound(SoundBase);
		//PlayerInfo->Audio = UGameplayStatics::CreateSound2D(PlayerInfo, SoundBase, 0.25f, 1.0f, 0.0f, nullptr, true, false);
		//PlayerInfo->Audio->Play(); 
		//PlayerInfo->Audio = UGameplayStatics::SpawnSound2D(GetWorld(), SoundBase, 1.0f, 1.0f, 0.0f, nullptr, true, false);
	}

}

void AMainMenuGameMode::EnableMouse()
{
	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerControllerRef->SetShowMouseCursor(true);
}

void AMainMenuGameMode::LaunchGame(FString Name, int MapIndex)
{
	if (MapIndex < MapAssets.Num())
	{
		PlayerInfo->PlayerName = Name;
		PlayerInfo->CurrentLevel = MapIndex;
		PlayerInfo->MapAssets = MapAssets;
		PlayerInfo->MainMenuLevelName = MainMenuName;//GetWorld()->GetMapName();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, PlayerInfo->MainMenuLevelName);

		PlayerInfo->GameLevelName = GameLevelName;

		UGameplayStatics::OpenLevel(GetWorld(), FName(*GameLevelName));
	}
}

