// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "ElectricDamageType.h"

FString UElectricDamageType::getText()
{
	return "Un bon coup de jus";
}

float UElectricDamageType::getMultiplier(EAbsType absorderType)
{
	switch (absorderType) {
	case(EAbsType::Shield) :
		return 2.f;
	}
	return Super::getMultiplier(absorderType);
}