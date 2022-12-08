// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_PlaceTower.h"

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
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
