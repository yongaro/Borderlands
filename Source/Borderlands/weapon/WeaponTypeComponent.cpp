// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponTypeComponent.h"
#include "Borderlands.h"
#include "Weapon.h"


// Sets default values for this component's properties
UWeaponTypeComponent::UWeaponTypeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// bWantsBeginPlay = true; // deprecated
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponTypeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponTypeComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!bCanBeFired)
	{
		if (LastFiringTime < OuterWeapon->RateOfFire)
		{
			LastFiringTime += DeltaTime;
		}
		else
		{
			bCanBeFired = true;
		}
	}
}

void UWeaponTypeComponent::onFire()
{
	bCanBeFired = false;
}

void UWeaponTypeComponent::onReload()
{

}

void UWeaponTypeComponent::onHold()
{

}

