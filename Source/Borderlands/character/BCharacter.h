// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
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
	FVector GetCameraLocation();
	FRotator GetCameraRotation();
	void traceLine(FHitResult& HitResult);

	//Inventory
	class AWeapon* Weapon;
	void SpawnWeapon(struct FWeaponInventoryItem);
};
