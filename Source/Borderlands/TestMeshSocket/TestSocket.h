// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TestSocket.generated.h"
//#include "Runtime/Engine/Classes/Animation/AnimSequence.h"

UCLASS()
class BORDERLANDS_API ATestSocket : public APawn
{
	GENERATED_BODY()
	
	class USkeletalMeshComponent* MeshComp;
	class USkeletalMeshComponent* HeadMesh;
	class UAnimSequence* Anime;

public:
	// Sets default values for this pawn's properties
	ATestSocket();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
