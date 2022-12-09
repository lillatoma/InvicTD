// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicTower.h"
#include "Components/MeshComponent.h"
#include "../InvicTD.h"


#include "InvicTD\GAS\GAS_AbilitySystemComponent.h"
#include "InvicTD\GAS\GAS_AttributeSet.h"
#include "InvicTD\GAS\GAS_GameplayAbility.h"
#include <GameplayEffectTypes.h>


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

// Called every frame
void AInvicTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
