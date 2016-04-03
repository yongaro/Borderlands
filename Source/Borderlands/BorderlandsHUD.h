// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "BorderlandsHUD.generated.h"

UCLASS()
class BORDERLANDS_API ABorderlandsHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	// Initializes the Slate UI and adds it as widget content to the game viewport.
	virtual void PostInitializeComponents() override;

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	// Reference to the Main Menu Slate UI.
	TSharedPtr<class SInGameUI> InGameUI;

	//Update methods
	void UpdateAmmunitionAmount(uint8 AmmoInMagazine, uint8 AmmoInReserve);
	void UpdateHealthAmount(bool HasHealthAmount, uint8 CurrentHealthAmount, uint8 MaximumHealthAmount);

	/*-----HUD information to display-----*/
	//Ammunition
	uint8 AmmoInMagazine;
	uint8 AmmoInReserve;
	//Absorbers
	bool HasHealthAbsorber;
	uint8 CurrentHealthAmount;
	uint8 MaximumHealthAmount;
	bool HasShieldAbsorber;
	uint8 CurrentShieldAmount;
	uint8 MaximumShieldAmount;
	bool HasArmorAbsorber;
	uint8 CurrentArmorAmount;
	uint8 MaximumArmorAmount;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

