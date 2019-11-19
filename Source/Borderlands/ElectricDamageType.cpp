// Fill out your copyright notice in the Description page of Project Settings.

#include "ElectricDamageType.h"
#include "Borderlands.h"

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