// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "BCharacter.h"
#include "BorderlandsPlayerController.h"

ABorderlandsPlayerController::ABorderlandsPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
}

ABorderlandsPlayerController::~ABorderlandsPlayerController()
{
}

void ABorderlandsPlayerController::SetupInputComponent()
{
	//check(InputComponent);
	//Actions
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABorderlandsPlayerController::CommandJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABorderlandsPlayerController::CommandStopJumping);

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
