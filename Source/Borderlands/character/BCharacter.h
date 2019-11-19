// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "../weapon/WeaponGraphic.h"
#include "BCharacter.generated.h"

UCLASS()
class BORDERLANDS_API ABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Movement
	void GoForward(float value);
	void GoRight(float value);
	void Turn(float value);
	void LookUp(float value);

	float BaseTurnRate;
	float BaseLookUpRate;
	UCameraComponent* CameraComponent;
	USkeletalMeshComponent* FirstPersonMesh;
	class UAnimSequence* IdleAnimation;

	//Weapon system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class AWeapon> DefaultWeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FVector WeaponOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FRotator WeaponRotation;
	bool bIsFiringDisabled;
	void onFire();
	void onStopFire();
	void BeginReload();
	void EndReload();

	FVector GetCameraLocation();
	FRotator GetCameraRotation();
	void traceLine(FHitResult& HitResult);
	void updateAmmunitionAmountOnHUD(uint8, uint8);
	void UpdateHealthAmountOnHUD(bool, uint8, uint8);
	void UpdateShieldAmountOnHUD(bool, uint8, uint8);
	void UpdateArmorAmountOnHUD(bool, uint8, uint8);

	//Inventory
	class AWeapon* Weapon;
	void SpawnWeapon(struct FWeaponInventoryItem);

	//Damage Handler
	class UDamageHandler* DamageHandler;
	virtual float TakeDamage
		(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	//Components
	void Connect(UActorComponent* comp);
};
