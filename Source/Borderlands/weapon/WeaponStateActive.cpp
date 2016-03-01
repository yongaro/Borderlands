// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Weapon.h"
#include "WeaponStateActive.h"

UWeaponStateActive::UWeaponStateActive()
{
}

UWeaponStateActive::~UWeaponStateActive()
{
}

bool UWeaponStateActive::BeginFiringSequence(bool bClientFired)
{
	if (GetOuterWeapon() != NULL && GetOuterWeapon()->WeaponTypeComponent != NULL)
	{
		GetOuterWeapon()->bIsFiring = true;
		return true;
	}
	return false;
}

bool UWeaponStateActive::EndFiringSequence(bool bClientFired)
{
	if (GetOuterWeapon() != NULL && GetOuterWeapon()->WeaponTypeComponent != NULL)
	{
		GetOuterWeapon()->bIsFiring = false;
		return true;
	}
	return false;
}
