// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_PlayerInfo.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UGI_PlayerInfo::StartPlayingSound(USoundBase* Sound)
{
	Audio = UGameplayStatics::CreateSound2D(this, Sound, 0.25f, 1.0f, 0.0f, nullptr, true, false);
	Audio->Play();
}
