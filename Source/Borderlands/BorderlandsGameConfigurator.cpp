// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "character/BCharacter.h"
#include "character/BorderlandsPlayerController.h"
#include "weapon/RifleWeaponTypeComponent.h"
#include "weapon/PistolWeaponTypeComponent.h"
#include "MyDamageType.h"
#include "ElectricDamageType.h"
#include "DamageHandler.h"
#include "BorderlandsGameConfigurator.h"

UBorderlandsGameConfigurator::UBorderlandsGameConfigurator()
{
	//Default values ...
}

UBorderlandsGameConfigurator::~UBorderlandsGameConfigurator()
{

}

bool UBorderlandsGameConfigurator::LoadFeaturesFromFile()
{
	FString GameDir = FPaths::GameDir();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GameDir);
	FString FileData = "";
	FString CompleteFilePath = GameDir + "default.config";

	FFileHelper::LoadFileToString(FileData, *CompleteFilePath);
	//UE_LOG(LogTemp, Warning, TEXT("FileData : \"%s\""), *FileData);
	if (FileData == "")
	{
		return false;
	}

	FileData.ParseIntoArrayLines(features, true);
	for (auto& str : features)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	return true;
}

bool UBorderlandsGameConfigurator::HasFeature(FString feature)
{
	return features.Contains(feature);
}

uint32 UBorderlandsGameConfigurator::GetFeaturesCount()
{
	return features.Num();
}

void UBorderlandsGameConfigurator::ConfigureGame(UWorld* world)
{
	if (world != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Configuring game..."));
		class ABorderlandsPlayerController* playerController = Cast<ABorderlandsPlayerController>(world->GetFirstPlayerController());
		if (playerController != nullptr)
		{
			class ABCharacter* playerCharacter = Cast<ABCharacter>(playerController->GetPawn());
			if (playerCharacter != nullptr)
			{
				//DamageHandler
				UDamageHandler* damageHandler = NewObject<UDamageHandler>(playerCharacter, UDamageHandler::StaticClass());
				if (HasFeature("Health"))
				{
					UAbsorber* healthAbsorber = NewObject<UAbsorber>(damageHandler, UAbsorber::StaticClass());
					healthAbsorber->type = EAbsType::Flesh;
					healthAbsorber->amount = 100.f;
					healthAbsorber->maxAmount = 100.f;
					damageHandler->addAbsorber(healthAbsorber);
				}
				if (HasFeature("Shield"))
				{
					UAbsorber* shieldAbsorber = NewObject<UAbsorber>(damageHandler, UAbsorber::StaticClass());
					shieldAbsorber->type = EAbsType::Shield;
					shieldAbsorber->amount = 100.f;
					shieldAbsorber->maxAmount = 100.f;
					damageHandler->addAbsorber(shieldAbsorber);
				}
				if (HasFeature("Armor"))
				{
					UAbsorber* armorAbsorber = NewObject<UAbsorber>(damageHandler, UAbsorber::StaticClass());
					armorAbsorber->type = EAbsType::Armor;
					armorAbsorber->amount = 100.f;
					armorAbsorber->maxAmount = 100.f;
					damageHandler->addAbsorber(armorAbsorber);
				}
				playerCharacter->Connect(damageHandler);
				UE_LOG(LogTemp, Warning, TEXT("DamageHandler connecte"));

				//Weapons
				playerController->Weapons.Empty();

				FWeaponInventoryItem weapon1;
				weapon1.AmmunitionPool = 60;
				weapon1.Damage = 10;
				weapon1.DamageAmount = 80;
				weapon1.MagazineSize = 30;
				weapon1.RateOfFire = 0.1f;
				weapon1.Manufacturer = EManufacturer::Jakobs;
				if (HasFeature("Electric"))
				{
					weapon1.DamageEvent.DamageTypeClass = UElectricDamageType::StaticClass();
				}
				else
				{
					weapon1.DamageEvent.DamageTypeClass = UMyDamageType::StaticClass();
				}
				if (HasFeature("Auto"))
				{
					weapon1.WeaponTypeComponentClass = URifleWeaponTypeComponent::StaticClass();
				}
				else if (HasFeature("Semi-Auto"))
				{
					weapon1.WeaponTypeComponentClass = UPistolWeaponTypeComponent::StaticClass();
				}
				else
				{
					weapon1.WeaponTypeComponentClass = UWeaponTypeComponent::StaticClass();
				}
				playerController->Weapons.Add(weapon1);
				UE_LOG(LogTemp, Warning, TEXT("Arme 1 ajoute"));

				FWeaponInventoryItem weapon2;
				weapon2.AmmunitionPool = 60;
				weapon2.Damage = 40;
				weapon2.DamageAmount = 80;
				weapon2.MagazineSize = 30;
				weapon2.RateOfFire = 0.4f;
				weapon2.Manufacturer = EManufacturer::Jakobs;
				weapon2.DamageEvent.DamageTypeClass = UMyDamageType::StaticClass();
				if (HasFeature("Semi-Auto"))
				{
					weapon2.WeaponTypeComponentClass = UPistolWeaponTypeComponent::StaticClass();
				}
				else if (HasFeature("Auto"))
				{
					weapon2.WeaponTypeComponentClass = URifleWeaponTypeComponent::StaticClass();
				}
				else
				{
					weapon2.WeaponTypeComponentClass = UWeaponTypeComponent::StaticClass();
				}
				playerController->Weapons.Add(weapon2);
				UE_LOG(LogTemp, Warning, TEXT("Arme 2 ajoute"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Err : playerCharacter == nullptr (in UBorderlandsGameConfigurator::ConfigureGame)"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Err : playerController == nullptr (in UBorderlandsGameConfigurator::ConfigureGame)"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Err : world == nullptr (in UBorderlandsGameConfigurator::ConfigureGame)"));
	}
}
