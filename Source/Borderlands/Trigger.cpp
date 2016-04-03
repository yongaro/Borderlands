// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Trigger.h"


// Sets default values
ATrigger::ATrigger()

{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(NAME_Default);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnTriggerOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATrigger::OnTriggerOverlapEnd);
	this->RootComponent = TriggerBox;
}



// Called when the game starts or when spawned

void ATrigger::BeginPlay()

{
	Super::BeginPlay();
}
// Called every frame
void ATrigger::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);
}



void ATrigger::OnTriggerOverlapBegin(AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != NULL && OtherActor != this ) {
		UE_LOG(LogTemp, Warning, TEXT("OnTriggerOverlapBegin"));
		OverlapStart();
	}
}
void ATrigger::OnTriggerOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor != NULL && OtherActor != this ) {
		UE_LOG(LogTemp, Warning, TEXT("OnTriggerOverlapEnd"));
	}	
}

bool ATrigger::addObjectToTrigger(UObject* obj) {
	if (obj->GetClass()->ImplementsInterface(UTriggerableInterface::StaticClass())) {
		triggerActions.Add(obj);
		return true;
	}
	return false;
}

void ATrigger::OverlapStart()
{
	UE_LOG(LogTemp, Warning, TEXT("OverlapStart"));
	for (UObject* o : triggerActions) {
		ITriggerableInterface::Execute_onTriggerActivated(o);
	}
}

void ATrigger::OverlapEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("OverlapEnd"));
	for (UObject* o : triggerActions) {
		ITriggerableInterface::Execute_onTriggerDesactivated(o);
	}
}




