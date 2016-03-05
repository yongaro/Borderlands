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
	
	virtual void SetupInputComponent();

	//Movement commands
	void CommandJump();
	void CommandStopJumping();
	void CommandGoForward(float value);
	void CommandGoRight(float value);
	void CommandTurn(float value);
	void CommandLookUp(float value);
};
