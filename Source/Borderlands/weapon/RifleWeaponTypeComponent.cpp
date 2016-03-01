// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Weapon.h"
#include "CollidingPawn.h"
#include "RifleWeaponTypeComponent.h"

URifleWeaponTypeComponent::URifleWeaponTypeComponent()
{
	//Super(); //mdr ca fait crash
	PrimaryComponentTick.bCanEverTick = true;
}

URifleWeaponTypeComponent::~URifleWeaponTypeComponent()
{
}

void URifleWeaponTypeComponent::onFire()
{
	Super::onFire();
	if (OuterWeapon != NULL) 
	{
		if (LastFiringTime >= OuterWeapon->RateOfFire)
		{
			LastFiringTime = 0;
			UE_LOG(LogTemp, Warning, TEXT("PAN"));

			FHitResult HitResult;
			OuterWeapon->Owner->traceLine(HitResult);
			//		UE_LOG(LogTemp, Warning, TEXT("Hit :  %s"), HitResult.GetActor()->GetName());
					//Ici, on pourra faire un traitement sur l'Actor touché par le tracage, du genre OuterWeapon->InflictDamageTo(HitResult.GetActor());
		}
	}
}

void URifleWeaponTypeComponent::onReload()
{

}

