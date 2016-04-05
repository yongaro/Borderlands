// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Absorber.h"
#include "weapon/Weapon.h"
#include "CharacterStatusInterface.h"
#include "DamageHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BORDERLANDS_API UDamageHandler : public UActorComponent , public ICharacterStatusInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageHandler();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void InitializeComponent() override;

	
	virtual void addAbsorber(UAbsorber* abs);

	virtual void updateHUD();

	// Hérité via ICharacterStatusInterface
	virtual uint8 getAbsorberMaxAmount_Implementation(EAbsType abstype);

	virtual uint8 getAbsorberAmount_Implementation(EAbsType abstype);

	virtual uint8 getAbsorberCount_Implementation();

	virtual bool HasAbsorberOfType_Implementation(EAbsType abstype);

	virtual bool Damage_Implementation(uint8 damageAmount, const FDamageEvent &DamageEvent);

private:
	TArray<UAbsorber*> absorbers;
	float dotTimer;
	uint8 dotCount;
	FMyDamageEvent* dot;

	

};
