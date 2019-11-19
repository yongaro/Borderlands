// Fill out your copyright notice in the Description page of Project Settings.

#include "RifleWeaponTypeComponent.h"
#include "Borderlands.h"
#include "Weapon.h"
#include "../character/BCharacter.h"

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

			FHitResult HitResult;
			OuterWeapon->Owner->traceLine(HitResult);
			if (HitResult.GetActor() != nullptr)
			{
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

