// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BorderlandsHUD.h"
#include "Borderlands.h"
#include "Engine.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "ui/SInGameUI.h"

ABorderlandsHUD::ABorderlandsHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;

	AmmoInMagazine = 0;
	AmmoInReserve = 0;

	HasHealthAbsorber = false;
	CurrentHealthAmount = 5;
	MaximumHealthAmount = 5;

	HasShieldAbsorber = false;
	CurrentShieldAmount = 5;
	MaximumShieldAmount = 5;

	HasArmorAbsorber = false;
	CurrentArmorAmount = 5;
	MaximumArmorAmount = 5;
}


void ABorderlandsHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SAssignNew(InGameUI, SInGameUI).BorderlandsHUD(this);

	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(InGameUI.ToSharedRef()));
	}
}

void ABorderlandsHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
										   (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)) );

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void ABorderlandsHUD::UpdateAmmunitionAmount(uint8 AmmoInMag, uint8 AmmoInR)
{
	this->AmmoInMagazine = AmmoInMag;
	this->AmmoInReserve = AmmoInR;
}

void ABorderlandsHUD::UpdateHealthAmount(bool HasHealthAbs, uint8 CurrentHealthAm, uint8 MaximumHealthAm)
{
	this->HasHealthAbsorber = HasHealthAbs;
	this->CurrentHealthAmount = CurrentHealthAm;
	this->MaximumHealthAmount = MaximumHealthAm;
}

void ABorderlandsHUD::UpdateShieldAmount(bool HasShieldAbs, uint8 CurrentShieldAm, uint8 MaximumShieldAm)
{
	this->HasShieldAbsorber = HasShieldAbs;
	this->CurrentShieldAmount = CurrentShieldAm;
	this->MaximumShieldAmount = MaximumShieldAm;
}

void ABorderlandsHUD::UpdateArmorAmount(bool HasArmorAbs, uint8 CurrentArmorAm, uint8 MaximumArmorAm)
{
	this->HasArmorAbsorber = HasArmorAbs;
	this->CurrentArmorAmount = CurrentArmorAm;
	this->MaximumArmorAmount = MaximumArmorAm;
}

