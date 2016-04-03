// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TriggerableInterface.h"
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
	/*Ajoute une un objet au tableau et verifie qu'il implement TriggerableInterface retourne faux cas echeant*/
	virtual bool addObjectToTrigger(UObject* obj);

	UPROPERTY(VisibleAnywhere, Category = "Triggers")
		UBoxComponent*  TriggerBox;

protected:

	UFUNCTION()
		virtual void OnTriggerOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		virtual void OnTriggerOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	/*Tableau des actions a trigger*/
	TArray<UObject*> triggerActions;
	/*Override this*/
	virtual void OverlapStart();
	virtual void OverlapEnd();
};
