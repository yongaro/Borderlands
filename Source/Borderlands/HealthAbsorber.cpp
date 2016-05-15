// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "HealthAbsorber.h"

UHealthAbsorber::UHealthAbsorber()
{
	type = EAbsType::Flesh;
	amount = 100.f;
	maxAmount = 100.f;
}


