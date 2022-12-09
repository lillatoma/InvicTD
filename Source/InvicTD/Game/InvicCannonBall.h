// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvicTD/GAS/GAS_GameplayAbility.h"

#include "InvicCannonBall.generated.h"

UCLASS()
class INVICTD_API AInvicCannonBall : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

public:

	class AInvicEnemy* Target;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 500.0f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Prereqs")
		TSubclassOf< UGameplayEffect > DamageEffect;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void TryMovingTowardsTarget(float DeltaTime);

public:	
	// Sets default values for this actor's properties
	AInvicCannonBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
