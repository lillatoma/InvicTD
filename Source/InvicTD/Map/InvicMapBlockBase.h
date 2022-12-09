// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvicMapBuilder.h"

#include "InvicMapBlockBase.generated.h"

UCLASS()
class INVICTD_API AInvicMapBlockBase : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	AInvicMapBlockBase();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTileType(EMB_TileType type);
	EMB_TileType GetTileType() const;

	bool CanTowerBeBuilt() const;
	void MarkBuildTower();

private:
	UPROPERTY(EditAnywhere)
		EMB_TileType Type = EMB_TileType::None;

	bool hasTower = false;


};
