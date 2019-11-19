// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Borderlands.h"
#include "CollidingPawn.h"
#include "WeaponState.h"
#include "WeaponStateActive.h"
#include "WeaponTypeComponent.h"
#include "WeaponGraphic.h"
#include "WeapGraphicComp.h"
#include "ElectricDamageType.h"
#include "../character/BCharacter.h"



// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VisualRepresentation"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("VisualRepresentation"));
	//A remplacer par le composant definitif
	/*
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
	*/
	
	currentTotalAmmunition = 180;
	
	
	
	//Create weapon type component (gameplay)
	WeaponTypeComponent = CreateDefaultSubobject<UWeaponTypeComponent>(TEXT("WeaponTypeComponent"));
	WeaponTypeComponent->OuterWeapon = this;

	//Set default firing state
	CurrentState = CreateDefaultSubobject<UWeaponStateActive>(TEXT("WeaponState")); //Attention : "new" fait crash UE
	CurrentState->OuterWeapon = this;
	//CurrentState->Log();
	bIsFiring = false;
	bHasFired = false;
	damageEvent.DamageTypeClass = UElectricDamageType::StaticClass();
	damageEvent.dps = 15;
	damageEvent.effectChance = 0.8f;
	damageAmount = 80;
}
// Called when the game starts or when spawned
void AWeapon::BeginPlay(){
	Super::BeginPlay();
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters params;
		params.Owner = this;
		// params.bNoCollisionFail = true;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FVector loc = GetActorLocation();
		FRotator rotation = FRotator::ZeroRotator;
		WVisual = world->SpawnActor<AWeaponGraphic>(AWeaponGraphic::StaticClass(),loc,rotation,params);
		
		if( WVisual != NULL ){
			WVisual->attachTo(this, TEXT("Root"), EAttachLocation::SnapToTargetIncludingScale, true);
		}
	}
}

// Called every frame
void AWeapon::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
	FiringSequence(DeltaTime);
}

void AWeapon::DestroyWeapon()
{
	if (WVisual != nullptr)
	{
		WVisual->Destroy();
	}
	Destroy();
}

void AWeapon::FiringSequence(float DeltaTime){
	if (WeaponTypeComponent != NULL && bIsFiring){
		if (currentAmmunitionInMagazine > 0){
			if( WVisual != NULL ){ WVisual->fire(); } //Passage a modifier pour le mode de  tir auto
			WeaponTypeComponent->onFire();
			bHasFired = true;
		}
		//else{
		//	reload();
		//}
	}

	//On fini la rafale de tir
	if (WeaponTypeComponent != NULL && !bIsFiring && bHasFired)
	{
		WeaponTypeComponent->onHold();
		bHasFired = false;
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
	if (Owner != NULL && !Owner->bIsFiringDisabled) {

		bool bClientFired = BeginFiringSequence(false);
		// Network code here
		/*if (Role < ROLE_Authority)
		{
			ServerStartFire(bClientFired);
		}*/
		//https://wiki.unrealengine.com/Create_A_Custom_Weapon_-_How_Firing_Works
	}
}

void AWeapon::EndFire()
{
	if (Owner != NULL)
	{
		bool bClientFired = EndFiringSequence(false);
		// Network code here
		/*if (Role < ROLE_Authority)
		{
		ServerStartFire(bClientFired);
		}*/
		//https://wiki.unrealengine.com/Create_A_Custom_Weapon_-_How_Firing_Works
	}
}

bool AWeapon::BeginFiringSequence(bool bClientFired)
{
	if (Owner != NULL){;
		bool bResult = CurrentState->BeginFiringSequence(bClientFired);
		return bResult;
	}
	return false;
}

bool AWeapon::EndFiringSequence(bool bClientFired)
{
	if (Owner != NULL)
	{
		bool bResult = CurrentState->EndFiringSequence(bClientFired);
		return bResult;
	}
	return false;
}

void AWeapon::reload(){
	if (currentAmmunitionInMagazine < MagazineSize && currentTotalAmmunition > 0){
		if( WVisual != NULL ){ WVisual->reload(); }
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

	//On connecte le WeaponTypeComponent
	UWeaponTypeComponent *NewWeaponTypeComponent = NewObject<UWeaponTypeComponent>(this, WeaponInventoryItem.WeaponTypeComponentClass);
	Connect(NewWeaponTypeComponent);
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

void AWeapon::Connect(UActorComponent * comp)
{
	auto weaponTypeComponent = Cast<UWeaponTypeComponent>(comp);
	if (weaponTypeComponent != nullptr)
	{
		weaponTypeComponent->OuterWeapon = this;
		if (!weaponTypeComponent->IsRegistered())
		{
			weaponTypeComponent->RegisterComponent();
		}
		if (WeaponTypeComponent != nullptr)
		{
			WeaponTypeComponent->DestroyComponent();
		}
		WeaponTypeComponent = weaponTypeComponent;
	}
}
