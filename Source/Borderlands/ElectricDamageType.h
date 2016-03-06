// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/DamageType.h"
#include "MyDamageType.h"
#include "ElectricDamageType.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API UElectricDamageType : public UMyDamageType
{
	GENERATED_BODY()
public:
	virtual float getMultiplier(EAbsType absorderType);
	FString getText();
};
