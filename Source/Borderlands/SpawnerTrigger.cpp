// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "SpawnActor.h"
#include "SpawnerTrigger.h"

ASpawnerTrigger::ASpawnerTrigger()
{
}

void ASpawnerTrigger::OverlapStart(AActor* OtherActor)
{

	TArray<AActor*> ovAct;
	TriggerBox->GetOverlappingActors(ovAct,ASpawnActor::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("Getting spawners %i"),ovAct.Num());

	for (AActor* sa : ovAct) {
		ASpawnActor* spawner = Cast<ASpawnActor>(sa);
		if (spawner!=NULL) {
			triggerActions.Add(spawner);
		}
	}
	Super::OverlapStart(OtherActor);
}