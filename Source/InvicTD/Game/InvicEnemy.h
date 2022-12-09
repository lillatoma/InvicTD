// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvicEnemy.generated.h"

UCLASS()
class INVICTD_API AInvicEnemy : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

#pragma region GAS
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
		class UGAS_AbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
		class UGAS_AttributeSet* Attributes;

public:
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual void InitializeAttributes();

	//Effect that initializes our default attributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	virtual void GiveAbilities();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TArray<TSubclassOf<class UGAS_GameplayAbility>> DefaultAbilities;



#pragma endregion


public:	
	// Sets default values for this actor's properties
	AInvicEnemy();

	TArray<FVector> Path;

	virtual void MoveToNextPathPoint(float DeltaTime);

	virtual void SetMovementSpeed(float speed);
	virtual float GetMovementSpeed() const;

	virtual void GetKilled();

	UPROPERTY(VisibleAnywhere)
		class AInvicEnemySpawner* Spawner;

	virtual float GetHealth() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int LatestPathPoint = 0;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 100.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
