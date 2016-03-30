// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Absorber.h"
#include "CharacterStatusInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class BORDERLANDS_API UCharacterStatusInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()	
};

class BORDERLANDS_API ICharacterStatusInterface
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
		bool HasAbsorberOfType(EAbsType abstype);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
		uint8 getAbsorberCount();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
		uint8 getAbsorberAmount(uint8 indexOfAbsorber);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
		uint8 getAbsorberMaxAmount(uint8 indexOfAbsorber);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
		bool Damage(uint8 damageAmount, FDamageEvent const & DamageEvent);
};