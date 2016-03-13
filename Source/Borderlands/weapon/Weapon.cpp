// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Weapon.h"
#include "CollidingPawn.h"
#include "WeaponState.h"
#include "WeaponStateActive.h"
#include "WeaponTypeComponent.h"
#include "ElectricDamageType.h"
#include "../character/BCharacter.h"



// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create visual representation of weapon (skeltal mesh)
	WeaponVisual = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VisualRepresentation"));
	//WeaponVisual->AttachTo(RootComponent);
	RootComponent = WeaponVisual;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponVisualAsset(TEXT("/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun"));
	if (WeaponVisualAsset.Succeeded())
	{
		WeaponVisual->SetSkeletalMesh(WeaponVisualAsset.Object);
		WeaponVisual->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	//Create weapon type component (gameplay)
	WeaponTypeComponent = CreateDefaultSubobject<UWeaponTypeComponent>(TEXT("WeaponTypeComponent"));
	WeaponTypeComponent->OuterWeapon = this;

	//Set default firing state
	CurrentState = CreateDefaultSubobject<UWeaponStateActive>(TEXT("WeaponState")); //Attention : "new" fait crash UE
	CurrentState->OuterWeapon = this;
	//CurrentState->Log();
	bIsFiring = false;
	damageEvent.DamageTypeClass = UElectricDamageType::StaticClass();
	damageEvent.dps = 15;
	damageEvent.effectChance = 0.8f;
	damageAmount = 80;
}
// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FiringSequence(DeltaTime);
}

void AWeapon::FiringSequence(float DeltaTime)
{
	if (WeaponTypeComponent != NULL && bIsFiring)
	{
		if (currentAmmunitionInMagazine > 0)
		{
			WeaponTypeComponent->onFire();
		}
		else
		{
			reload();
		}
	}
}

/*void AWeapon::fire()
{
	if(WeaponTypeComponent != NULL)
	{

		if (currentAmmunitionInMagazine > 0)
		{
			WeaponTypeComponent->onFire();
		}
		else
		{
			reload();
		}
	}
}*/

void AWeapon::StartFire()
{
	if (Owner != NULL && !Owner->bIsFiringDisabled)
	{
		bool bClientFired = BeginFiringSequence(false);
		//Code réseau ici, avec checking de role et envoi de message au serveur
		/*if (Role < ROLE_Authority)
		{
			ServerStartFire(bClientFired); 
		}*/
		//https://wiki.unrealengine.com/Create_A_Custom_Weapon_-_How_Firing_Works #pasdeblueprint
	}
}

void AWeapon::EndFire()
{
	if (Owner != NULL)
	{
		bool bClientFired = EndFiringSequence(false);
		//Code réseau ici, avec checking de role et envoi de message au serveur
		/*if (Role < ROLE_Authority)
		{
		ServerStartFire(bClientFired);
		}*/
		//https://wiki.unrealengine.com/Create_A_Custom_Weapon_-_How_Firing_Works #pasdeblueprint
	}
}

bool AWeapon::BeginFiringSequence(bool bClientFired)
{
	if (Owner != NULL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AWeapon::BeginFiringSequence()"));
		bool bResult = CurrentState->BeginFiringSequence(bClientFired);
		return bResult;
	}
	return false;
}

bool AWeapon::EndFiringSequence(bool bClientFired)
{
	if (Owner != NULL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AWeapon::EndFiringSequence()"));
		bool bResult = CurrentState->EndFiringSequence(bClientFired);
		return bResult;
	}
	return false;
}

void AWeapon::reload()
{
	if (currentAmmunitionInMagazine < MagazineSize && currentTotalAmmunition > 0)
	{
		WeaponTypeComponent->onReload();
	}
}

void AWeapon::resupply()
{
	currentAmmunitionInMagazine = MagazineSize;
}

void AWeapon::FromInventoryItem(FWeaponInventoryItem WeaponInventoryItem)
{
	Damage = WeaponInventoryItem.Damage;
	RateOfFire = WeaponInventoryItem.RateOfFire;
	MagazineSize = WeaponInventoryItem.MagazineSize;
	AmmunitionPool = WeaponInventoryItem.AmmunitionPool;
	Manufacturer = WeaponInventoryItem.Manufacturer;
	damageAmount = WeaponInventoryItem.DamageAmount;
	damageEvent = WeaponInventoryItem.DamageEvent;
	UWeaponTypeComponent *NewWeaponTypeComponent = NewObject<UWeaponTypeComponent>(this, WeaponInventoryItem.WeaponTypeComponentClass);
	if (NewWeaponTypeComponent != NULL)
	{
		NewWeaponTypeComponent->OuterWeapon = this;
		NewWeaponTypeComponent->RegisterComponent();
		WeaponTypeComponent->DestroyComponent();
		WeaponTypeComponent = NewWeaponTypeComponent;
	}
}

FWeaponInventoryItem AWeapon::ToInventoryItem()
{
	FWeaponInventoryItem Result;
	Result.Damage = this->Damage;
	Result.RateOfFire = this->RateOfFire;
	Result.MagazineSize = this->MagazineSize;
	Result.AmmunitionPool = this->AmmunitionPool;
	Result.Manufacturer = this->Manufacturer;
	Result.DamageAmount = this->damageAmount;
	Result.DamageEvent = this->damageEvent;
	Result.WeaponTypeComponentClass = this->WeaponTypeComponent->GetClass();
	return Result;
}
