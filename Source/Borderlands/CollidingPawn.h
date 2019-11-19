// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class BORDERLANDS_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Nos composants
	USphereComponent* SphereComponent;
	UStaticMeshComponent* SphereVisual;
	UParticleSystemComponent* OurParticleSystem;
	UCameraComponent* Camera;
	class UCollidingPawnMovementComponent* OurMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class AWeapon> WeaponClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FVector WeaponOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		FRotator WeaponRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);

	bool IsFiringDisabled();

	//Actions
	void onFire();
	void onStopFire();
	FVector GetCameraLocation();
	FRotator GetCameraRotation();
	void traceLine(FHitResult& HitResult);
	void ParticleToggle();

	//Test Weapon
	class AWeapon* Weapon;
};
