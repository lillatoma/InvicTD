// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StatsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UStatsDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	float GetTowerRange() const;
	float GetTowerDamage() const;
	float GetEnemyHealth() const;

private:
	UPROPERTY(EditAnywhere)
		float TowerRange;

	UPROPERTY(EditAnywhere)
		float TowerDamage;

	UPROPERTY(EditAnywhere)
		float EnemyHealth;

};
