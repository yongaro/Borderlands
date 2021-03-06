// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trigger.h"
#include "SpawnerTrigger.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API ASpawnerTrigger : public ATrigger{
	GENERATED_BODY()
	public:
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<class AActor> whatToSpawn;
	UPROPERTY(EditAnywhere, Category = "Config")
		int numToSpawn;
	UPROPERTY(EditAnywhere, Category = "Config")
		float timeBetweenSpawn;	
	UPROPERTY(EditAnywhere, Category = "Config")
		FVector offset;
	UPROPERTY(EditAnywhere, Category = "Config")
		bool bDestroyWhenFinished;

	int nbSpawned;

	// Sets default values for this actor's properties
	ASpawnerTrigger();
	// Called when the game starts or when spawned
	// Called every frame
	//virtual void Tick(float DeltaSeconds) override;
	private:
		virtual void OverlapStart(AActor* OtherActor) override;
		virtual void spawn();
};
