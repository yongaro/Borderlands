// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "DamageHandler.h"
#include "Engine.h"

// Sets default values for this component's properties
UDamageHandler::UDamageHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	/*health = 10;
	maxHealth = 350;
	regenRate = 50.f;
	time = 0;*/
	//armor = CreateDefaultSubobject<UAbsorber>(TEXT("Amount"));
	//absorbers = TArray<UAbsorbers*>();
	/*Example*/
	UAbsorber* abs = CreateDefaultSubobject<UAbsorber>(TEXT("Armure"));
	abs->setCoolDown(2.5f);
	abs->setRegenRate(200.f);
	abs->setMaxAmount(700);
	absorbers.Add(abs);
	abs = CreateDefaultSubobject<UAbsorber>(TEXT("Vie"));
	absorbers.Add(abs);
	// ...
}


// Called when the game starts
void UDamageHandler::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UDamageHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FString s;
	for (UAbsorber* abs : absorbers) {
		s += " - " + abs->GetName();
		s.AppendInt(abs->amount);
	}
	GEngine->AddOnScreenDebugMessage(
		1,
		5.f,
		FColor::Red,
		FString::Printf(TEXT("%s"), *s));
	// ...
}

bool UDamageHandler::Damage(int damageAmount, FString type)
{
	for (UAbsorber* abs : absorbers) {
		damageAmount = abs->absorb(damageAmount, type);
	}
	return damageAmount > 0;
}



