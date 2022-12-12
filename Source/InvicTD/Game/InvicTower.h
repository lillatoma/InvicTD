// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>

#include "InvicTower.generated.h"

UCLASS()
class INVICTD_API AInvicTower : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* CylMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* TurretMesh;


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

	UPROPERTY(EditAnywhere)
		float Range;
	UPROPERTY(EditAnywhere)
		float Damage;
	UPROPERTY(EditAnywhere)
		float TowerHeight = 100.0f;
	UPROPERTY(EditAnywhere)
		float CannonRotationSpeed = 540.0f;
	class AInvicEnemy* Target;

	FVector GetCannonLocation();

public:	
	// Sets default values for this actor's properties
	AInvicTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void FindEnemy();

	virtual void TryAttackEnemy();

	virtual void RotateCannonTowardsEnemy(float DeltaTime);

	class AInvicEnemySpawner* GetEnemyList();
	class AInvicEnemySpawner* EnemyList;

	UPROPERTY(EditAnywhere, Category = "Sounds")
		class USoundBase* PlaceSound;

	virtual void MakeTowerPlaceSound();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Prereqs")
		TSubclassOf<class UGameplayAbility> AttackAbility;
};
