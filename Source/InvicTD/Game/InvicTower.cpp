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
	Location.Z += 80.f;
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Distance: %.2f"), ClosestDistance));
	Target = (ClosestDistance <= Range) ? (AllEnemies[ClosestIndex]) : nullptr;
}

void AInvicTower::TryAttackEnemy()
{
	FindEnemy();

	if (Target)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("There is a target")));
		GetAbilitySystemComponent()->TryActivateAbilityByClass(AttackAbility);
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

// Called every frame
void AInvicTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TryAttackEnemy();
	
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
