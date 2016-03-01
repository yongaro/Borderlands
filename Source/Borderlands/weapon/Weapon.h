// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType, Category = Gameplay)
enum class EManufacturer : uint8{
	Torgue UMETA(DisplayName = "Torgue"),
	Dahl UMETA(DisplayName = "Dahl"),
	Jakobs UMETA(DisplayName = "Jakobs")
};

UCLASS()
class BORDERLANDS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		uint8 Damage;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float RateOfFire;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		uint8 MagazineSize;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		uint8 AmmunitionPool;
	UPROPERTY(EditAnywhere, Category = Gameplay)
		EManufacturer Manufacturer;
	
	void StartFire();
	void EndFire();
	bool BeginFiringSequence(bool bClientFired);
	bool EndFiringSequence(bool bClientFired);

	void FiringSequence(float DeltaTime);

	void reload();
	void resupply();

	class ACollidingPawn* Owner;
	USkeletalMeshComponent* WeaponVisual;
	uint8 currentAmmunitionInMagazine;
	uint8 currentTotalAmmunition;
	class UWeaponTypeComponent *WeaponTypeComponent;
	class UWeaponState* CurrentState;
	bool bIsFiring;

private:
	
};
