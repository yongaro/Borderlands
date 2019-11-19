// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BorderlandsGameMode.h"
#include "Borderlands.h"
#include "BorderlandsHUD.h"
#include "character/BorderlandsPlayerController.h"
#include "character/BCharacter.h"
#include "BorderlandsGameConfigurator.h"
#include "BorderlandsCharacter.h"

ABorderlandsGameMode::ABorderlandsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABorderlandsHUD::StaticClass();

	//Set our player controller
	PlayerControllerClass = ABorderlandsPlayerController::StaticClass();
	DefaultPawnClass = ABCharacter::StaticClass();
	//ABorderlandsPlayerController* PlayerController = PlayerControllerClass->GetDefaultObject<ABorderlandsPlayerController>();

	// gameConfigurator = ConstructObject<class UBorderlandsGameConfigurator>(UBorderlandsGameConfigurator::StaticClass());
	gameConfigurator = NewObject<class UBorderlandsGameConfigurator>(UBorderlandsGameConfigurator::StaticClass());

	bAreFeaturesLoaded = false;

	UE_LOG(LogTemp, Warning, TEXT("Configuring game..."));
	if (gameConfigurator->LoadFeaturesFromFile())
	{
		UE_LOG(LogTemp, Warning, TEXT("Features list loaded"));
		bAreFeaturesLoaded = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load the feature list"));
	}
}

void ABorderlandsGameMode::BeginPlay()
{
	if (bAreFeaturesLoaded)
	{
		gameConfigurator->ConfigureGame(GetWorld());
	}
}
