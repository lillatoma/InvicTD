// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvicMapBuilder.generated.h"

UENUM()
enum class EMB_TileType : uint8
{
	None,
	Path,
	High,
	PathScenery,
	PathScenery2,
	PathScenery3,
	HighScenery,
	HighScenery2,
	HighScenery3
};


UCLASS()
class INVICTD_API AInvicMapBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInvicMapBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};