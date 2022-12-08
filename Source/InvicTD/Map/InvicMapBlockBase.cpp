// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicMapBlockBase.h"

// Sets default values
AInvicMapBlockBase::AInvicMapBlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInvicMapBlockBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInvicMapBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInvicMapBlockBase::SetTileType(EMB_TileType type)
{
	Type = type;
}

EMB_TileType AInvicMapBlockBase::GetTileType() const
{
	return Type;
}

