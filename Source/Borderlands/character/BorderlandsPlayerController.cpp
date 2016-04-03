// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "BCharacter.h"
#include "../weapon/Weapon.h"
#include "../ElectricDamageType.h"
#include "../weapon/RifleWeaponTypeComponent.h"
#include "../BorderlandsHUD.h"
#include "BorderlandsPlayerController.h"

ABorderlandsPlayerController::ABorderlandsPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
	SetupInventory();
}

ABorderlandsPlayerController::~ABorderlandsPlayerController()
{
}

void ABorderlandsPlayerController::BeginPlay()
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->SpawnWeapon(Weapons[0]);
	}
}

void ABorderlandsPlayerController::SetupInputComponent()
{
	//check(InputComponent);
	//Movement Actions
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABorderlandsPlayerController::CommandJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABorderlandsPlayerController::CommandStopJumping);

	//Weapon Actions
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABorderlandsPlayerController::CommandFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ABorderlandsPlayerController::CommandStopFire);

	//Inventory Actions
	InputComponent->BindAction("ChangeWeapon1", IE_Pressed, this, &ABorderlandsPlayerController::CommandChangeWeapon1);
	InputComponent->BindAction("ChangeWeapon2", IE_Pressed, this, &ABorderlandsPlayerController::CommandChangeWeapon2);
	InputComponent->BindAction("ChangeWeapon3", IE_Pressed, this, &ABorderlandsPlayerController::CommandChangeWeapon3);
	InputComponent->BindAction("ChangeWeapon4", IE_Pressed, this, &ABorderlandsPlayerController::CommandChangeWeapon4);

	//Axis
	InputComponent->BindAxis("MoveForward", this, &ABorderlandsPlayerController::CommandGoForward);
	InputComponent->BindAxis("MoveRight", this, &ABorderlandsPlayerController::CommandGoRight);
	InputComponent->BindAxis("Turn", this, &ABorderlandsPlayerController::CommandTurn);
	InputComponent->BindAxis("LookUp", this, &ABorderlandsPlayerController::CommandLookUp);
}

void ABorderlandsPlayerController::CommandJump()
{
	auto ControlledCharacter = Cast<ACharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->Jump();
	}
}

void ABorderlandsPlayerController::CommandStopJumping()
{
	auto ControlledCharacter = Cast<ACharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->StopJumping();
	}
}

void ABorderlandsPlayerController::CommandGoForward(float value)
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->GoForward(value);
	}
}

void ABorderlandsPlayerController::CommandGoRight(float value)
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->GoRight(value);
	}
}

void ABorderlandsPlayerController::CommandTurn(float value)
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->Turn(value);
	}
}

void ABorderlandsPlayerController::CommandLookUp(float value)
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->LookUp(value);
	}
}

/*
	Ici, on pourra "configurer" les armes de départ du joueur (depuis un eventuel fichier XML ?)
*/
void ABorderlandsPlayerController::SetupInventory()
{
	//Pour l'instant, les armes sont en dures
	FWeaponInventoryItem Weapon1;
	Weapon1.AmmunitionPool = 60;
	Weapon1.Damage = 10;
	Weapon1.DamageAmount = 80;
	Weapon1.DamageEvent.DamageTypeClass = UElectricDamageType::StaticClass();
	Weapon1.MagazineSize = 30;
	Weapon1.Manufacturer = EManufacturer::Jakobs;
	Weapon1.RateOfFire = 0.1f;
	Weapon1.WeaponTypeComponentClass = URifleWeaponTypeComponent::StaticClass();
	Weapons.Add(Weapon1);

	FWeaponInventoryItem Weapon2;
	Weapon2.AmmunitionPool = 60;
	Weapon2.Damage = 10;
	Weapon2.DamageAmount = 80;
	Weapon2.DamageEvent.DamageTypeClass = UElectricDamageType::StaticClass();
	Weapon2.MagazineSize = 30;
	Weapon2.Manufacturer = EManufacturer::Jakobs;
	Weapon2.RateOfFire = 0.5f;
	Weapon2.WeaponTypeComponentClass = URifleWeaponTypeComponent::StaticClass();
	Weapons.Add(Weapon2);
}

void ABorderlandsPlayerController::CommandChangeWeapon1()
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->SpawnWeapon(Weapons[0]);
	}
}

void ABorderlandsPlayerController::CommandChangeWeapon2()
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->SpawnWeapon(Weapons[1]);
	}
}

void ABorderlandsPlayerController::CommandChangeWeapon3()
{
}

void ABorderlandsPlayerController::CommandChangeWeapon4()
{
}

void ABorderlandsPlayerController::CommandFire()
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->onFire();
	}
}

void ABorderlandsPlayerController::CommandStopFire()
{
	auto ControlledCharacter = Cast<ABCharacter>(this->GetPawn());
	if (ControlledCharacter != NULL)
	{
		ControlledCharacter->onStopFire();
	}
}

void ABorderlandsPlayerController::UpdateAmmunitionAmountOnHUD(uint8 AmmoInMagazine, uint8 AmmoInReserve)
{
	ABorderlandsHUD* BorderlandsHUD = Cast<ABorderlandsHUD>(GetHUD());
	if (BorderlandsHUD != NULL)
	{
		BorderlandsHUD->UpdateAmmunitionAmount(AmmoInMagazine, AmmoInReserve);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find BorderlandsHUD instance"));
	}
}

void ABorderlandsPlayerController::UpdateHealthAmountOnHUD(bool HasHealthAmount, uint8 CurrentHealthAmount, uint8 MaximumHealthAmount)
{
	ABorderlandsHUD* BorderlandsHUD = Cast<ABorderlandsHUD>(GetHUD());
	if (BorderlandsHUD != NULL)
	{
		BorderlandsHUD->UpdateHealthAmount(HasHealthAmount, CurrentHealthAmount, MaximumHealthAmount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find BorderlandsHUD instance"));
	}
}
