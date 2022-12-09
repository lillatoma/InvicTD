// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InvicTD/GAS/GAS_GameplayAbility.h"
#include "GA_SpawnProjectile.generated.h"

/**
 * 
 */
UCLASS()
class INVICTD_API UGA_SpawnProjectile : public UGAS_GameplayAbility
{
	GENERATED_BODY()
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> CannonBallActor;
};
