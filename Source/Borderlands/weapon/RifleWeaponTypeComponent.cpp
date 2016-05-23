// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Weapon.h"
#include "../character/BCharacter.h"
#include "RifleWeaponTypeComponent.h"

URifleWeaponTypeComponent::URifleWeaponTypeComponent()
{
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
					//UE_LOG(LogTemp, Warning, TEXT("Hit :  %s"), HitResult.GetActor()->GetName());
			if (HitResult.GetActor() != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit :  %s"), *HitResult.GetActor()->GetName());
				HitResult.GetActor()->TakeDamage(OuterWeapon->damageAmount, OuterWeapon->damageEvent, OuterWeapon->Owner->GetInstigatorController(), OuterWeapon->Owner);
			}
		}
	}
}

void URifleWeaponTypeComponent::onReload()
{

}

void URifleWeaponTypeComponent::onHold()
{

}

