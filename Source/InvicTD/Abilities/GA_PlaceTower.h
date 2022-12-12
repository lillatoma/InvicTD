// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InvicTD/GAS/GAS_GameplayAbility.h"
#include "GA_PlaceTower.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UGA_PlaceTower : public UGAS_GameplayAbility
{
	GENERATED_BODY()
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> TowerActor;
};
