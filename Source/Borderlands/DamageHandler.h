// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Absorber.h"
#include "DamageHandler.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BORDERLANDS_API UDamageHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageHandler();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual bool Damage(int damageAmount, FString type);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absorbers")
		TArray<UAbsorber*> absorbers;
	
};
