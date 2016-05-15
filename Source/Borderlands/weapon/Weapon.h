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

USTRUCT(BlueprintType)
struct FMyDamageEvent : public FRadialDamageEvent
{

	GENERATED_USTRUCT_BODY() //rend intelisense fou
	uint8 dps;
	float effectChance;
};

USTRUCT(BlueprintType)
struct FWeaponInventoryItem
{
	GENERATED_USTRUCT_BODY() //je confirme

public:
	uint8 Damage;
	float RateOfFire;
	uint8 MagazineSize;
	uint8 AmmunitionPool;
	EManufacturer Manufacturer;
	uint8 DamageAmount;
	FMyDamageEvent DamageEvent;
	TSubclassOf<class UActorComponent> WeaponTypeComponentClass;
	//A ajouter : Modele de l'arme
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

	//On supprime l'acteur et sa composante graphique
	void DestroyWeapon();

	//Caractéristiques de l'arme
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
	uint8 damageAmount;
	FMyDamageEvent damageEvent;

	//Caractéristiques de l'instance de l'arme
	uint8 currentAmmunitionInMagazine;
	uint8 currentTotalAmmunition;
	bool bIsFiring;
	bool bHasFired;

	//Mécaniques de tir
	void StartFire();
	void EndFire();
	bool BeginFiringSequence(bool bClientFired);
	bool EndFiringSequence(bool bClientFired);
	void FiringSequence(float DeltaTime);

	//Manipulation des caractéristiques de l'arme
	void reload();
	void resupply();
	void FromInventoryItem(FWeaponInventoryItem);
	FWeaponInventoryItem ToInventoryItem();
	void Connect(UActorComponent* comp);

	//Composants de l'acteur
	//class ACollidingPawn* Owner;
	class ABCharacter* Owner;
	
	//A remplacer par un composant WeaponGraphic
	USkeletalMeshComponent* WeaponVisual;
	
	class AWeaponGraphic* WVisual;
	
	
	
	//####################################
	
	class UWeaponTypeComponent *WeaponTypeComponent;
	class UWeaponState* CurrentState;
	
};

