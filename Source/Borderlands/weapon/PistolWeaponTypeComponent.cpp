// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Weapon.h"
#include "../character/BCharacter.h"
#include "PistolWeaponTypeComponent.h"

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
			UE_LOG(LogTemp, Warning, TEXT("PAN"));

			FHitResult HitResult;
			OuterWeapon->Owner->traceLine(HitResult);
			//UE_LOG(LogTemp, Warning, TEXT("Hit :  %s"), HitResult.GetActor()->GetName());
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



