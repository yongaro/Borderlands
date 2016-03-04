// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DamageHandler.h"
#include "DamageActor.generated.h"

UCLASS()
class BORDERLANDS_API ADamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	virtual float TakeDamage
		(float DamageAmount, struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;
	UDamageHandler* dmgHandler;
};
