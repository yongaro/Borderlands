// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "weapon/WeaponTypeComponent.h"
#include "PistolWeaponTypeComponent.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API UPistolWeaponTypeComponent : public UWeaponTypeComponent
{
	GENERATED_BODY()
	
public:
	
	UPistolWeaponTypeComponent();
	~UPistolWeaponTypeComponent();
	
	//Weapon behaviors
	virtual void onFire();
	virtual void onReload();
	virtual void onHold();

private:
	bool bHasFired;
};
