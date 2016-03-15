// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Trigger.generated.h"

UCLASS()
class BORDERLANDS_API ATrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	UPROPERTY(VisibleAnywhere, Category = "Triggers")
		UBoxComponent*  TriggerBox;
	
	//not yet 
	UPROPERTY(EditAnywhere, Category = "Triggers")
		TSubclassOf<class AActor> whatToSpawn;

	UFUNCTION()
		virtual void OnTriggerOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		virtual void OnTriggerOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	
};
