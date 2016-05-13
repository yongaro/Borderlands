// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Borderlands.h"
#include "BorderlandsGameMode.h"
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

	gameConfigurator = ConstructObject<class UBorderlandsGameConfigurator>(UBorderlandsGameConfigurator::StaticClass());

	bAreFeaturesLoaded = false;

	UE_LOG(LogTemp, Warning, TEXT("Configurateur cree"));
	if (gameConfigurator->LoadFeaturesFromFile())
	{
		UE_LOG(LogTemp, Warning, TEXT("Features chargees"));
		bAreFeaturesLoaded = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Erreur chargement des features"));
	}
}

void ABorderlandsGameMode::BeginPlay()
{
	if (bAreFeaturesLoaded)
	{
		gameConfigurator->ConfigureGame(GetWorld());
	}
}
