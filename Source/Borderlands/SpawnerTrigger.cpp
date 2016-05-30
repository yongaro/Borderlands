// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "SpawnActor.h"
#include "SpawnerTrigger.h"

ASpawnerTrigger::ASpawnerTrigger(){
	nbSpawned = 0;
}

void ASpawnerTrigger::OverlapStart(AActor* OtherActor)
{

	TArray<AActor*> ovAct;
	//TriggerBox->GetOverlappingActors(ovAct,ASpawnActor::StaticClass());
	//UE_LOG(LogTemp, Warning, TEXT("Getting spawners %i"),ovAct.Num());

	//for (AActor* sa : ovAct) {
		//ASpawnActor* spawner = Cast<ASpawnActor>(sa);
		//if (spawner!=NULL) {
			//triggerActions.Add(spawner);
		//}
	//}
	spawn();
	Super::OverlapStart(OtherActor);
}


void ASpawnerTrigger::spawn(){
	if(whatToSpawn!=NULL){
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters params;
			params.Owner = this;
			params.bNoCollisionFail = true;
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
