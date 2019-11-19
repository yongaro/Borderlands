// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerTrigger.h"
#include "Borderlands.h"
#include "SpawnActor.h"


ASpawnerTrigger::ASpawnerTrigger(){
	nbSpawned = 0;
}

void ASpawnerTrigger::OverlapStart(AActor* OtherActor)
{

	// TArray<AActor*> ovAct;
	spawn();
	Super::OverlapStart(OtherActor);
}


void ASpawnerTrigger::spawn(){
	if(whatToSpawn!=NULL){
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters params;
			params.Owner = this;
			// params.bNoCollisionFail = true; obosolete replaced by NoFail or the handling override.
			// params.bNoFail = true;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FVector loc = GetActorLocation()+offset;
			FRotator rotation = FRotator::ZeroRotator;
			rotation.Yaw = 90.f;
			AActor *a = world->SpawnActor<AActor>(whatToSpawn, loc, rotation, params);
			++nbSpawned;
			if( nbSpawned < numToSpawn){ 
				FTimerHandle timerHandler;
				GetWorldTimerManager().SetTimer(timerHandler, this, &ASpawnerTrigger::spawn, timeBetweenSpawn, false);
			}
		}
		if(bDestroyWhenFinished && nbSpawned >= numToSpawn){ Destroy(); }
	}
}
