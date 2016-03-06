// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Absorber.generated.h"

UENUM(BlueprintType, Category = Gameplay)
enum class EAbsType : uint8 {
	Shield UMETA(DisplayName = "Shield"),
	Flesh UMETA(DisplayName = "Flesh"),
	Armor UMETA(DisplayName = "Armor")
};

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
	virtual void InitializeComponent() override;
	virtual void regen(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	EAbsType type;
	float amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 maxAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float regenRate;
	float time;
	float coolDown;
	
};
