// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicCannonBall.h"
#include "InvicTower.h"
#include "InvicEnemy.h"

#include "StatsDataAsset.h"
#include "InvicTD\Menu\GI_PlayerInfo.h"

#include "InvicTD\GAS\GAS_AbilitySystemComponent.h"
#include "InvicTD\GAS\GAS_AttributeSet.h"
#include "InvicTD\GAS\GAS_GameplayAbility.h"
#include <GameplayEffectTypes.h>

// Sets default values
AInvicCannonBall::AInvicCannonBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"), true);


}

// Called when the game starts or when spawned
void AInvicCannonBall::BeginPlay()
{
	Super::BeginPlay();

	//Check if mesh overlaps anything
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AInvicCannonBall::OverlapBegin);
}

// Called every frame
void AInvicCannonBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TryMovingTowardsTarget(DeltaTime);
}

void AInvicCannonBall::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AInvicEnemy* Enemy = Cast<AInvicEnemy>(OtherActor);

	if (Enemy)
	{
		if (GetOwner())
		{
			AInvicTower* Tower = Cast<AInvicTower>(GetOwner());

			if (Tower)
			{
				//Damage the enemy with how much damage is written inside the stats asset
				auto Context = Tower->GetAbilitySystemComponent()->MakeEffectContext();
				Context.AddSourceObject(Tower);
				UGI_PlayerInfo* Info = Cast<UGI_PlayerInfo>(GetGameInstance());

				Tower->GetAbilitySystemComponent()->BP_ApplyGameplayEffectToTarget(
					DamageEffect, Enemy->GetAbilitySystemComponent(), Info->StatsAsset->GetTowerDamage(), Context);
				Enemy->GetDamaged();
				if (Enemy->GetHealth() <= 0)
					Enemy->GetKilled(); 
			}

		}
		Destroy();
	}
}

void AInvicCannonBall::TryMovingTowardsTarget(float DeltaTime)
{
	//If the target still exists, we move towards it
	//Otherwise this cannonball is not needed
	if(IsValid(Target))
	{
		FVector Location = GetActorLocation();
		double DistanceToCover = DeltaTime * MoveSpeed;
		FVector Dist = Target->GetActorLocation() - Location;
		FVector DistNormal = Dist.GetSafeNormal();
		double Length = Dist.Length();
		if (DistanceToCover > Length)
			DistanceToCover = Length;

		SetActorLocation(Location + DistNormal * DistanceToCover);
	}
	else Destroy();
}
