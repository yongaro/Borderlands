// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/DamageType.h"
#include "ElectricDamageType.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API UElectricDamageType : public UDamageType
{
	GENERATED_BODY()
public:
		static FString getText();
};
