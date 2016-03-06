// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/DamageType.h"
#include "Absorber.h"
#include "MyDamageType.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API UMyDamageType : public UDamageType
{
	GENERATED_BODY()	
	public:
		virtual float getMultiplier(EAbsType absorderType);
	
};
