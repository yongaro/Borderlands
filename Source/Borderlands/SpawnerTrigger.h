// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trigger.h"
#include "SpawnerTrigger.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API ASpawnerTrigger : public ATrigger
{
	GENERATED_BODY()
	public:
	// Sets default values for this actor's properties
	ASpawnerTrigger();
	// Called when the game starts or when spawned
	// Called every frame
	//virtual void Tick(float DeltaSeconds) override;
	private:
		virtual void OverlapStart(AActor* OtherActor) override;
};
