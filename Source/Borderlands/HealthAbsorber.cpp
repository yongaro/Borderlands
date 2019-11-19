// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthAbsorber.h"
#include "Borderlands.h"


UHealthAbsorber::UHealthAbsorber()
{
	type = EAbsType::Flesh;
	amount = 100.f;
	maxAmount = 100.f;
}


