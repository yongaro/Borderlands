// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "WeaponState.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API UWeaponState : public UObject
{
public:
	GENERATED_BODY()

	UWeaponState();
	~UWeaponState();

	virtual bool BeginFiringSequence(bool bClientFired) { return false; }
	virtual bool EndFiringSequence(bool bClientFired) { return false; }

	class AWeapon* OuterWeapon;
	AWeapon* GetOuterWeapon() const { return OuterWeapon; }
};
