// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvicGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API AInvicGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Map Builder")
		TSubclassOf<class AInvicMapBuilder> MapGenerator;


};
