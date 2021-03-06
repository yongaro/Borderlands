// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageHandler.h"
#include "Borderlands.h"
#include "character/BCharacter.h"
#include "DamageActor.h"
#include "Engine.h"

// Sets default values for this component's properties
UDamageHandler::UDamageHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// bWantsBeginPlay = true; // Always true from now on ?
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	/*UAbsorber* temp=CreateDefaultSubobject<UAbsorber>("Life");
	temp->type = EAbsType::Flesh;
	absorbers.Add(temp);*/
	dotTimer = 0;
	
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
	//FString s=GetOwner()->GetName();
	/*FString s = OuterActor->GetName();
	for (UAbsorber* abs : absorbers) {
		s += " - " + abs->GetName()+ " : ";
		s.AppendInt(abs->amount);
	}
	GEngine->AddOnScreenDebugMessage(
		1,
		5.f,
		FColor::Red,
		FString::Printf(TEXT("%s"), *s));*/
	// ...

	if (dotCount > 0 && dotTimer > 60) {
		dotTimer = 0;
		dotCount--;
		Damage(dot->dps,*dot);
	}
	else {
		if (dotCount > 0) {
			dotTimer += DeltaTime;
		}
	}
}

void UDamageHandler::InitializeComponent()
{
	//ADamageActor *dmg = Cast<ADamageActor>(GetOwner());
	ADamageActor *dmg = Cast<ADamageActor>(OuterActor);
	if (dmg) {
		dmg->dmgHandler = this; 
	}

	//Init HUD on player
	updateHUD();
}


void UDamageHandler::addAbsorber(UAbsorber * abs)
{
	if (!absorbers.Contains(abs)) {
		absorbers.Insert(abs, 0);
	}
}

void UDamageHandler::updateHUD()
{
	//ABCharacter* BCharacter = Cast<ABCharacter>(GetOwner());
	ABCharacter* BCharacter = Cast<ABCharacter>(OuterActor);
	if (BCharacter)
	{
		if (this->Execute_HasAbsorberOfType(this, EAbsType::Flesh))
		{
			BCharacter->UpdateHealthAmountOnHUD(true, this->Execute_getAbsorberAmount(this, EAbsType::Flesh), this->Execute_getAbsorberMaxAmount(this, EAbsType::Flesh));
		}
		if (this->Execute_HasAbsorberOfType(this, EAbsType::Shield))
		{
			BCharacter->UpdateShieldAmountOnHUD(true, this->Execute_getAbsorberAmount(this, EAbsType::Shield), this->Execute_getAbsorberMaxAmount(this, EAbsType::Shield));
		}
		if (this->Execute_HasAbsorberOfType(this, EAbsType::Armor))
		{
			BCharacter->UpdateArmorAmountOnHUD(true, this->Execute_getAbsorberAmount(this, EAbsType::Armor), this->Execute_getAbsorberMaxAmount(this, EAbsType::Armor));
		}
	}
}

uint8 UDamageHandler::getAbsorberMaxAmount_Implementation(EAbsType abstype)
{
	for (UAbsorber* a : absorbers) {
		if (a->type == abstype)
			return a->getMaxAmount();
	}
	return -1;
}

uint8 UDamageHandler::getAbsorberAmount_Implementation(EAbsType abstype)
{
	for (UAbsorber* a : absorbers) {
		if (a->type == abstype)
			return a->getAmount();
	}
	return -1;
}


uint8 UDamageHandler::getAbsorberCount_Implementation()
{
	uint8 count = absorbers.Num();
	return count;
}

bool UDamageHandler::HasAbsorberOfType_Implementation(EAbsType abstype)
{
	for (UAbsorber* a : absorbers) {
		if (a->type == abstype)
			return true;
	}
	return false;
}

bool UDamageHandler::Damage_Implementation(uint8 damageAmount, const FDamageEvent &DamageEvent)
{
	FMyDamageEvent* f;
	if (DamageEvent.IsOfType(FMyDamageEvent::ClassID)) {
		f = (FMyDamageEvent*)&DamageEvent;
		if (FMath::SRand() < f->effectChance) {
			dot = f;
			dotCount = 5; //dur�e des effets ?
			dotTimer = 0;
		}
	}
	for (UAbsorber* abs : absorbers) {
		damageAmount = abs->absorb(damageAmount, DamageEvent);
	}

	updateHUD();
	return absorbers.Last()->getAmount() <= 0;
}



