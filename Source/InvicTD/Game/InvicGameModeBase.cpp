// Fill out your copyright notice in the Description page of Project Settings.


#include "InvicGameModeBase.h"
#include "InvicTD\Map\InvicMapBuilder.h"

#include "Kismet/GameplayStatics.h"

void AInvicGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//Try spawning the mapgenerator
	AActor* MapGenActor = GetWorld()->SpawnActor<AActor>(MapGenerator, FVector(), FRotator());

	AInvicMapBuilder* MapGen = Cast<AInvicMapBuilder>(MapGenActor);


}
