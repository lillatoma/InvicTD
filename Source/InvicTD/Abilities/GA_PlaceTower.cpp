// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_PlaceTower.h"
#include "InvicTD\Map\InvicMapBlockBase.h"
#include "InvicTD\Map\InvicMapBuilder.h"

#include "Kismet/GameplayStatics.h"

void UGA_PlaceTower::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//FVector WorldLocation, WorldDirection;
	//if (PlayerControllerRef->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("WorldLocation (%.2f|%.2f|%.2f"), WorldDirection.X, WorldDirection.Y, WorldDirection.Z));

	//}

	FHitResult HitResult;
	if (PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, HitResult.HitObjectHandle.FetchActor()->GetName()); 
		AActor* Floor = HitResult.HitObjectHandle.FetchActor();
		if (Floor)
		{
			AInvicMapBlockBase* Block = Cast<AInvicMapBlockBase>(Floor);
			if (Block && Block->CanTowerBeBuilt())
			{
				FVector Location = Block->GetActorLocation();
				Location.Z = HitResult.ImpactPoint.Z;

				AActor* Object = GetWorld()->SpawnActor<AActor>(TowerActor, Location, FRotator());
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Location (%.2f|%.2f|%.2f"), Location.X, Location.Y, Location.Z));

				if(Object)
					Block->MarkBuildTower();
			}
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
