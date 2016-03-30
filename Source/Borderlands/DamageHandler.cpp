// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "DamageHandler.h"

#include "DamageActor.h"
#include "Engine.h"

// Sets default values for this component's properties
UDamageHandler::UDamageHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	UAbsorber* temp=CreateDefaultSubobject<UAbsorber>("Life");
	temp->type = EAbsType::Flesh;
	absorbers.Add(temp);
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
	FString s=GetOwner()->GetName();
	for (UAbsorber* abs : absorbers) {
		s += " - " + abs->GetName()+ " : ";
		s.AppendInt(abs->amount);
	}
	GEngine->AddOnScreenDebugMessage(
		1,
		5.f,
		FColor::Red,
		FString::Printf(TEXT("%s"), *s));
	// ...

	if (dotCount > 0 && dotTimer > 60) {
		UE_LOG(LogTemp, Warning, TEXT("Application du DOT"));
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
	ADamageActor *dmg = Cast<ADamageActor>(GetOwner());
	if (dmg) {
		dmg->dmgHandler = this; 
	}
}


void UDamageHandler::addAbsorber(UAbsorber * abs)
{
	if (!absorbers.Contains(abs)) {
		absorbers.Insert(abs, 0);
	}
}

uint8 UDamageHandler::getAbsorberMaxAmount_Implementation(uint8 indexOfAbsorber)
{
	if (absorbers.IsValidIndex(indexOfAbsorber))
		return absorbers[indexOfAbsorber]->getMaxAmount();
	UE_LOG(LogTemp, Warning, TEXT("Invalid index"));
	return 0;
}

uint8 UDamageHandler::getAbsorberAmount_Implementation(uint8 indexOfAbsorber)
{
	if (absorbers.IsValidIndex(indexOfAbsorber))
		return absorbers[indexOfAbsorber]->getAmount();
	UE_LOG(LogTemp, Warning, TEXT("Invalid index"));
	return 0;
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
			UE_LOG(LogTemp, Warning, TEXT("EFFET"));
			dot = f;
			dotCount = 5; //durée des effets ?
			dotTimer = 0;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("PAS D EFFET"));
		}
	}
	for (UAbsorber* abs : absorbers) {
		damageAmount = abs->absorb(damageAmount, DamageEvent);
	}
	return absorbers.Last()->getAmount() <= 0;
}

/*bool UDamageHandler::Damage_Implementation(uint8 damageAmount, FDamageEvent const & DamageEvent)
{
	FMyDamageEvent* f;
	if (DamageEvent.IsOfType(FMyDamageEvent::ClassID)) {
		f = (FMyDamageEvent*)&DamageEvent;
		if (FMath::SRand() < f->effectChance) {
			UE_LOG(LogTemp, Warning, TEXT("EFFET"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("PAS D EFFET"));
		}
	}
	for (UAbsorber* abs : absorbers) {
		damageAmount = abs->absorb(damageAmount, DamageEvent);
	}
	return damageAmount > 0;
}*/




