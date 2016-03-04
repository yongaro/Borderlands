// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Absorber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BORDERLANDS_API UAbsorber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbsorber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void setMaxAmount(int32 maxAmount);
	virtual void setRegenRate(float regentRate);
	virtual void setCoolDown(float coolDown);

	virtual int getAmount();
	virtual int absorb(int damageAmount, FDamageEvent const & DamageEvent);
	virtual void regen(float DeltaTime);

	float amount;
	int32 maxAmount;
	float regenRate;
	float time;
	float coolDown;
	
};
