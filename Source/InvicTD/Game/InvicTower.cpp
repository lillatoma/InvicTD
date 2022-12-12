// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicTower.h"
#include "Components/MeshComponent.h"
#include "../InvicTD.h"

#include "InvicEnemySpawner.h"
#include "InvicEnemy.h"


#include "InvicTD\GAS\GAS_AbilitySystemComponent.h"
#include "InvicTD\GAS\GAS_AttributeSet.h"
#include "InvicTD\GAS\GAS_GameplayAbility.h"
#include <GameplayEffectTypes.h>

#include "Kismet/GameplayStatics.h"

FVector AInvicTower::GetCannonLocation()
{
	FVector Location = GetActorLocation();
	Location.Z += TowerHeight;
	return Location;
}

// Sets default values
AInvicTower::AInvicTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CylMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cylinder Mesh");
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	
	if (CylMesh)
		RootComponent = CylMesh;

	if(TurretMesh)
		TurretMesh->SetupAttachment(CylMesh);

	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UGAS_AttributeSet>("Attributes");
}

// Called when the game starts or when spawned
void AInvicTower::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
	MakeTowerPlaceSound();
	//BeginPlay();
}

void AInvicTower::FindEnemy()
{
	if (!GetEnemyList())
		return;

	auto AllEnemies = EnemyList->GetEnemyList();
	int ENum = AllEnemies.Num();

	if (ENum == 0)
	{
		Target = nullptr;
		return;
	}
	int ClosestIndex = 0;
	float ClosestDistance = FVector::Distance(GetActorLocation(), AllEnemies[0]->GetActorLocation());

	for (int i = 1; i < ENum; i++)
	{
		float Distance = FVector::Distance(GetActorLocation(), AllEnemies[i]->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestIndex = i;

		}
	}
	Target = (ClosestDistance <= Range) ? (AllEnemies[ClosestIndex]) : nullptr;
}

void AInvicTower::TryAttackEnemy()
{
	FindEnemy();

	if (Target)
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(AttackAbility);
	}
}

void AInvicTower::RotateCannonTowardsEnemy(float DeltaTime)
{
	if (Target)
	{
		FVector Dist = Target->GetActorLocation() - GetActorLocation();
		FRotator DesiredRotation = Dist.Rotation();
		DesiredRotation.Yaw -= 90.f;
		float MaxRotation = DeltaTime * CannonRotationSpeed;

		FRotator CurrentRotation = TurretMesh->GetComponentRotation();
		
		float YawDiff = DesiredRotation.Yaw - CurrentRotation.Yaw;
		while (YawDiff > 180.f)
			YawDiff -= 360.f;
		while (YawDiff < -180.f)
			YawDiff += 360.f;

		FRotator EndRotation = CurrentRotation;

		if (YawDiff < 0.f)
		{
			if (YawDiff < -MaxRotation)
				EndRotation.Yaw += -MaxRotation;
			else
				EndRotation.Yaw += YawDiff;
		}
		else if (YawDiff > 0.f)
		{
			if (YawDiff > MaxRotation)
				EndRotation.Yaw += MaxRotation;
			else
				EndRotation.Yaw += YawDiff;
		}


		TurretMesh->SetWorldRotation(EndRotation);
	}
}

AInvicEnemySpawner* AInvicTower::GetEnemyList()
{
	if (EnemyList)
		return EnemyList;

	AActor* EnemySpawnerActor = UGameplayStatics::GetActorOfClass(GetWorld(), AInvicEnemySpawner::StaticClass());
	if (EnemySpawnerActor)
	{
		AInvicEnemySpawner* EnemySpawner = Cast<AInvicEnemySpawner>(EnemySpawnerActor);
		if (EnemySpawner)
		{
			EnemyList = EnemySpawner;
			return EnemyList;
		}
	}
	return nullptr;

}

void AInvicTower::MakeTowerPlaceSound()
{
	if (PlaceSound)
		UGameplayStatics::SpawnSound2D(GetWorld(), PlaceSound, 0.25f);
}

// Called every frame
void AInvicTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TryAttackEnemy();
	RotateCannonTowardsEnemy(DeltaTime); 
}

UAbilitySystemComponent* AInvicTower::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AInvicTower::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void AInvicTower::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf < UGAS_GameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));

		}
	}
}
