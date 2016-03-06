// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "Absorber.h"
#include "DamageHandler.h"
#include "ElectricDamageType.h"



// Sets default values for this component's properties
UAbsorber::UAbsorber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
	maxAmount = 350; /*dummy default values*/
	amount = 0;
	regenRate = 20.f;
	time = 0;
	coolDown = 2;
	type = EAbsType::Shield;
	/*UActorComponent* comp= GetOwner()->FindComponentByClass(UDamageHandler::StaticClass());
	UDamageHandler *dmg = Cast<UDamageHandler>(comp);
	if (dmg) {
		dmg->absorbers.Add(this);
	}*/
	// ...
}


// Called when the game starts
void UAbsorber::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UAbsorber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (time<0)
		time += DeltaTime;
	else
		regen(DeltaTime);
	// ...
}

void UAbsorber::setMaxAmount(int32 maxAmount)
{
	this->maxAmount = maxAmount;
	amount = maxAmount;
}

void UAbsorber::setRegenRate(float regenRate)
{
	this->regenRate = regenRate;
}

void UAbsorber::setCoolDown(float coolDown)
{
	this->coolDown = coolDown;
}

int UAbsorber::getAmount()
{
	return amount;
}

int UAbsorber::absorb(int damageAmount, FDamageEvent const & DamageEvent)
{
	float multiplier = 1.f;
	UMyDamageType *DamageType = Cast<UMyDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());
	if (DamageType) {
		multiplier = DamageType->getMultiplier(this->type);
	}
	UE_LOG(LogTemp, Warning, TEXT("Absorbing %i * %f"), damageAmount, multiplier);
	int unAbsorbed = 0;
	if (damageAmount > amount) {
		unAbsorbed = damageAmount - amount;
		UE_LOG(LogTemp, Warning, TEXT("%s didn't absorb %i"), *GetName(), unAbsorbed);
	}
	amount = FMath::Max(0,(int)( amount - damageAmount*multiplier));
	time = -coolDown;
	return unAbsorbed;
}

void UAbsorber::InitializeComponent()
{
	UActorComponent* comp = GetOwner()->FindComponentByClass(UDamageHandler::StaticClass());
	UDamageHandler *dmg = Cast<UDamageHandler>(comp);
	if (dmg) {
		dmg->absorbers.Add(this);
	}
}

void UAbsorber::regen(float DeltaTime)
{
	if (amount < maxAmount) {
		float newAmount = amount + regenRate*DeltaTime;
		amount = fmin(maxAmount, newAmount);
	}
}


