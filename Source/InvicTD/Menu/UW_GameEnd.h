// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_GameEnd.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UUW_GameEnd : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetWinloseText(bool won);
	UFUNCTION(BlueprintCallable)
		void OnButtonClick();

};
