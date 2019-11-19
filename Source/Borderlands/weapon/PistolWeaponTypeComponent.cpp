// Fill out your copyright notice in the Description page of Project Settings.

#include "PistolWeaponTypeComponent.h"
#include "Borderlands.h"
#include "Weapon.h"
#include "../character/BCharacter.h"


UPistolWeaponTypeComponent::UPistolWeaponTypeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bHasFired = false;
}

UPistolWeaponTypeComponent::~UPistolWeaponTypeComponent()
{
}

void UPistolWeaponTypeComponent::onFire()
{
	Super::onFire();
	if (OuterWeapon != NULL)
	{
		if (LastFiringTime >= OuterWeapon->RateOfFire && !bHasFired)
		{
			bHasFired = true;
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

void UPistolWeaponTypeComponent::onReload()
{

}

void UPistolWeaponTypeComponent::onHold()
{
	bHasFired = false;
}



