// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FPTest.generated.h"

UCLASS()
class BORDERLANDS_API AFPTest : public APawn
{
	GENERATED_BODY()

	class USkeletalMeshComponent* MeshComp;
	class UAnimSequence* Anime;
	
	
public:
	// Sets default values for this pawn's properties
	AFPTest();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
