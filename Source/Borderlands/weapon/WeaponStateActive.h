// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponState.h"
#include "WeaponStateActive.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API UWeaponStateActive : public UWeaponState
{
	GENERATED_BODY()

public:

	UWeaponStateActive();
	~UWeaponStateActive();

	virtual bool BeginFiringSequence(bool bClientFired);
	virtual bool EndFiringSequence(bool bClientFired);
};
