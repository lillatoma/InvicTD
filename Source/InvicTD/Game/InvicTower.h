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


public:	
	// Sets default values for this actor's properties
	AInvicTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
