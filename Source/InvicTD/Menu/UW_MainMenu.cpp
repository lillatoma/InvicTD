// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MainMenu.h"
#include "MainMenuGameMode.h"
#include "Misc/Char.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


FString UUW_MainMenu::CheckForNumericTextAndTrim(FString InputText, int MaxLength)
{
	
	if (InputText.Len() <= 0)
		return InputText;

	//If the text isn't numeric, we remove the last char added
	//It trims the text in both cases to not be larger than MaxLength

	if (InputText.IsNumeric())
	{
		while(InputText.Len() > MaxLength)
			InputText.RemoveAt(InputText.Len() - 1);
	}
	else
	{
		do //We have to remove last char because it is not numeric
		{
			InputText.RemoveAt(InputText.Len() - 1);
		}
		while  (InputText.Len() > MaxLength);
	}
	return InputText;
}

FString UUW_MainMenu::TrimNameInputText(FString InputText, int MaxLength)
{
	if (InputText.Len() <= 0)
		return InputText;


	while(InputText.Len() > MaxLength)
		InputText.RemoveAt(InputText.Len() - 1);

	return InputText;
}

void UUW_MainMenu::CloseGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit,false);
}

void UUW_MainMenu::TryStartGame()
{
	if (NumInputText.Len() > 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, NumInputText);
		int map = FCString::Atoi(*NumInputText);
		map--;

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Map is %d"), map));
		if (map >= 0 && map <= 9)
		{
			AMainMenuGameMode* GameMode = Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode());
			if(GameMode)
				GameMode->LaunchGame(NameInputText, map);
		}
	}


}
