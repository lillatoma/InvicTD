// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicEnemy.h"
#include "InvicEnemySpawner.h"
#include "InvicGameModeBase.h"
#include "InvicTD\GAS\GAS_AbilitySystemComponent.h"
#include "InvicTD\GAS\GAS_AttributeSet.h"
#include "InvicTD\GAS\GAS_GameplayAbility.h"
#include <GameplayEffectTypes.h>

#include "Kismet/GameplayStatics.h"

// Sets default values
AInvicEnemy::AInvicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("UFO Mesh");
	if (Mesh)
	{
		Mesh->SetSimulatePhysics(true);
	}

	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UGAS_AttributeSet>("Attributes");
}

void AInvicEnemy::MoveToNextPathPoint(float DeltaTime)
{
	FVector CurrentPosition = GetActorLocation();
	
	if (LatestPathPoint < Path.Num() - 1)
	{
		float TotalDistanceToCover = DeltaTime * MovementSpeed;
		FVector NextPathPoint = Path[LatestPathPoint + 1];
		
		FVector Diff = (NextPathPoint - CurrentPosition);
		FVector DiffNormal = Diff.GetSafeNormal();
		FVector NextMovementPosition = CurrentPosition;

		if (Diff.Length() <= TotalDistanceToCover)
		{
			LatestPathPoint++;
			TotalDistanceToCover -= Diff.Length();
			NextMovementPosition = NextPathPoint;

			if (LatestPathPoint < Path.Num() - 1)
			{
				if (TotalDistanceToCover > 0)
				{
					NextPathPoint = Path[LatestPathPoint + 1];

					Diff = (NextPathPoint - NextMovementPosition);
					DiffNormal = Diff.GetSafeNormal();
					NextMovementPosition += DiffNormal * TotalDistanceToCover;
				}
			}
			else
			{
				//Lose
				AInvicGameModeBase* GameMode = Cast<AInvicGameModeBase>(GetWorld()->GetAuthGameMode());
				if (GameMode)
				{
					GameMode->PreloseGame();
				}
			}
		}
		else
		{
			NextMovementPosition += DiffNormal * TotalDistanceToCover;
		}
		
		SetActorLocation(NextMovementPosition);

	}
}

void AInvicEnemy::SetMovementSpeed(float speed)
{
	MovementSpeed = speed;
}

void AInvicEnemy::GetDamaged()
{
	if(HitSound)
		UGameplayStatics::SpawnSound2D(GetWorld(), HitSound,0.25f);
}

void AInvicEnemy::GetKilled()
{
	if (DeathSound)
		UGameplayStatics::SpawnSound2D(GetWorld(), DeathSound,0.25f);
	Spawner->RemoveEnemyFromList(this);
	AInvicGameModeBase* GameMode = Cast<AInvicGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnEnemyKilled();
		if (Spawner->CountEnemiesLeft() == 0)
		{
			{
				GameMode->PrewinGame();
			}
		}
	}

	Destroy();
}

float AInvicEnemy::GetMovementSpeed() const
{
	return MovementSpeed;
}

// Called when the game starts or when spawned
void AInvicEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes(); 
	GiveAbilities();
}

// Called every frame
void AInvicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToNextPathPoint(DeltaTime);
}

UAbilitySystemComponent* AInvicEnemy::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AInvicEnemy::InitializeAttributes()
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

void AInvicEnemy::GiveAbilities()
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

float AInvicEnemy::GetHealth() const
{
	return Attributes->GetHealth();
}