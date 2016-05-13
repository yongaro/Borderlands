// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponTypeComponent.h"
#include "RifleWeaponTypeComponent.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API URifleWeaponTypeComponent : public UWeaponTypeComponent
{
	GENERATED_BODY()
	
public:

	URifleWeaponTypeComponent();
	~URifleWeaponTypeComponent();

	//Weapon behaviors
	virtual void onFire();
	virtual void onReload();
	virtual void onHold();
};
