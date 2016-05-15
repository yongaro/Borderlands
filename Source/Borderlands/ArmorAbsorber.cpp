// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "ArmorAbsorber.h"

UArmorAbsorber::UArmorAbsorber()
{
	type = EAbsType::Armor;
	amount = 100.f;
	maxAmount = 100.f;
}


