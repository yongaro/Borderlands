// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldAbsorber.h"
#include "Borderlands.h"


UShieldAbsorber::UShieldAbsorber()
{
	type = EAbsType::Shield;
	amount = 100.f;
	maxAmount = 100.f;
}


