// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_SpawnProjectile.h"
#include "InvicTD\Game\InvicTower.h"
#include "InvicTD\Game\InvicCannonBall.h"

#include "Kismet/GameplayStatics.h"


void UGA_SpawnProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (ActorInfo->OwnerActor.Get())
	{
		AInvicTower* Tower = Cast<AInvicTower>(ActorInfo->OwnerActor);
		if (Tower)
		{
			FTransform SpawnTransform(FRotator(), Tower->GetCannonLocation(), FVector(1, 1, 1));

			AInvicCannonBall* CannonBall = Cast<AInvicCannonBall>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, CannonBallActor, SpawnTransform));

			if (CannonBall)
			{
				CannonBall->Target = Tower->Target;
				CannonBall->SetOwner(ActorInfo->OwnerActor.Get());
				UGameplayStatics::FinishSpawningActor(CannonBall, SpawnTransform);
			}

		}
	}

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{

	}

	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}





