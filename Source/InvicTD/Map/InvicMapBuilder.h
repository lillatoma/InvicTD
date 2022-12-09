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

	UPROPERTY(EditAnywhere)
		class UMapDataAsset* MapAsset;

	UPROPERTY(EditAnywhere)
		float TileDistance = 100.0f;

	UPROPERTY(EditAnywhere)
		float ConvertZ = 50.0f;

public:	
	// Sets default values for this actor's properties
	AInvicMapBuilder();

	virtual class UMapDataAsset* GetAsset() const;
	virtual float GetTileDistance() const;

	virtual FVector ConvertGridToWorld(FIntPoint point) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void BuildMapFromMapAsset();
	virtual void BuildMapFromString(FIntPoint Size, char* String);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
