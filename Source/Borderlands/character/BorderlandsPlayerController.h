// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BorderlandsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API ABorderlandsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABorderlandsPlayerController();
	~ABorderlandsPlayerController();
	
	virtual void BeginPlay();
	virtual void SetupInputComponent();

	//Movement commands
	void CommandJump();
	void CommandStopJumping();
	void CommandGoForward(float value);
	void CommandGoRight(float value);
	void CommandTurn(float value);
	void CommandLookUp(float value);

	//Inventory data
	TArray<struct FWeaponInventoryItem> Weapons;
	void SetupDefaultInventory();

	//Inventory commands
	void CommandChangeWeapon1();
	void CommandChangeWeapon2();
	void CommandChangeWeapon3();
	void CommandChangeWeapon4();

	//Weapon commands
	void CommandFire();
	void CommandStopFire();
	void CommandBeginReload();

	//HUD commands
	void UpdateAmmunitionAmountOnHUD(uint8 AmmoInMagazine, uint8 AmmoInReserve);
	void UpdateHealthAmountOnHUD(bool HasHealthAmount, uint8 CurrentHealthAmount, uint8 MaximumHealthAmount);
	void UpdateShieldAmountOnHUD(bool HasShieldAmount, uint8 CurrentShieldAmount, uint8 MaximumShieldAmount);
	void UpdateArmorAmountOnHUD(bool HasArmorAmount, uint8 CurrentArmorAmount, uint8 MaximumArmorAmount);
};
