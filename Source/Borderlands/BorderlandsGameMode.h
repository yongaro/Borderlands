// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BorderlandsGameMode.generated.h"

UCLASS(minimalapi)
class ABorderlandsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABorderlandsGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class UBorderlandsGameConfigurator* gameConfigurator;
	bool bAreFeaturesLoaded;
};



