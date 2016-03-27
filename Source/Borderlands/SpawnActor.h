// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

UCLASS()
class BORDERLANDS_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	UStaticMeshComponent* Mesh;
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<class AActor> whatToSpawn;
	UPROPERTY(EditAnywhere, Category = "Config")
		FVector offset;
	UPROPERTY(EditAnywhere, Category = "Config")
		bool bDestroyWhenFinished;
	virtual void spawn();
};