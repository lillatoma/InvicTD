// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Game.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UUW_Game : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTextFormat(FString t);

	void SetThePlayerName(FString n);

	UFUNCTION(BlueprintCallable)
		FString PutDataIntoFormat(int level, int enemiesKilled, int enemiesLeft);

	UFUNCTION(BlueprintImplementableEvent)
		FString SetTheText(int level, int enemiesKilled, int enemiesLeft);

private:

	UPROPERTY(EditAnywhere)
		FString TextFormat;

	UPROPERTY(EditAnywhere)
		FString name;

};
