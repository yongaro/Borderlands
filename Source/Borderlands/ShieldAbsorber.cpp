// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "ShieldAbsorber.h"

UShieldAbsorber::UShieldAbsorber()
{
	type = EAbsType::Shield;
	amount = 100.f;
	maxAmount = 100.f;
}


