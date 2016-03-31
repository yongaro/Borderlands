// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "TriggerableInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class BORDERLANDS_API UTriggerableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class BORDERLANDS_API ITriggerableInterface 
{
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
		bool onTriggerActivated();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
		bool onTriggerDesactivated();
};