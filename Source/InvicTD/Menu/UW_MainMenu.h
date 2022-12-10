// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UUW_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString NameInputText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString NumInputText;

	UFUNCTION(BlueprintCallable)
		FString CheckForNumericTextAndTrim(FString InputText, int MaxLength);

	UFUNCTION(BlueprintCallable)
		FString TrimNameInputText(FString InputText, int MaxLength);

	UFUNCTION(BlueprintCallable)
		void CloseGame();

	UFUNCTION(BlueprintCallable)
		void TryStartGame();
};

