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

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

