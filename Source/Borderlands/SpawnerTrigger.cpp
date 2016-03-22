// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "SpawnActor.h"
#include "SpawnerTrigger.h"

ASpawnerTrigger::ASpawnerTrigger()
{
}

void ASpawnerTrigger::OverlapStart()
{
	UE_LOG(LogTemp, Warning, TEXT("getting spawners"));

	TArray<AActor*> ovAct;
	TriggerBox->GetOverlappingActors(ovAct,ASpawnActor::StaticClass());
	for (AActor* sa : ovAct) {
		ASpawnActor* spawner = Cast<ASpawnActor>(sa);
		if (spawner!=NULL) {
			spawner->spawn();
		}
	}
}