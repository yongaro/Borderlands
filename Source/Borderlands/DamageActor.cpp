// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "DamageActor.h"
#include "ElectricDamageType.h"


// Sets default values
ADamageActor::ADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	dmgHandler = CreateDefaultSubobject<UDamageHandler>("handler");
	AddOwnedComponent(dmgHandler);
}

// Called when the game starts or when spawned
void ADamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

float ADamageActor::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	/*Test pour type de degats*/
	UElectricDamageType *DamageType = Cast<UElectricDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());
	if (DamageType) {
		UE_LOG(LogTemp, Warning, TEXT("Aie %s %i"), *(DamageType->getText()),DamageAmount);
	}
	
	if( dmgHandler->Damage(DamageAmount, DamageEvent))
		UE_LOG(LogTemp, Warning, TEXT("Je meurs"));
	return 0.0f;
}




