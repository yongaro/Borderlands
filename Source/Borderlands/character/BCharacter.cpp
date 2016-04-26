// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "../weapon/Weapon.h"
#include "../weapon/WeaponTypeComponent.h"
#include "../weapon/RifleWeaponTypeComponent.h"
#include "BorderlandsPlayerController.h"
#include "BCharacter.h"
/*
ENGINE_API void DrawDebugLine(
	const UWorld* InWorld,
	FVector const& LineStart,
	FVector const& LineEnd,
	FColor const& Color,
	bool bPersistentLines = false,
	float LifeTime = -1.f,
	uint8 DepthPriority = 0,
	float Thickness = 0.f
	);*/

// Sets default values
ABCharacter::ABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule and defaults turn rate values
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	//Camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachParent = GetCapsuleComponent();
	CameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	CameraComponent->bUsePawnControlRotation = true;

	//First person mesh
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->AttachParent = CameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	//First person skeletal mesh asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FirstPersonMeshAsset(TEXT("SkeletalMesh'/Game/Borderlands/characters/claptrap/FP/Skel_FragTrap_Arms.Skel_FragTrap_Arms'"));
	if (FirstPersonMeshAsset.Succeeded())
	{
		FirstPersonMesh->SetSkeletalMesh(FirstPersonMeshAsset.Object);
		FirstPersonMesh->SetRelativeLocation(FVector(15.0f, 0, -160.0f));
	}

	//First person skeletal mesh animation
	const ConstructorHelpers::FObjectFinder<UAnimSequence> IdleAnimationAsset(TEXT("AnimSequence'/Game/Borderlands/characters/claptrap/FP/AnimSet/1st_Person_Pistol/Idle_Anim.Idle_Anim'"));
	IdleAnimation = IdleAnimationAsset.Object;

	//Weapon System
	DefaultWeaponClass = AWeapon::StaticClass();
	bIsFiringDisabled = false;
	//Weapon offset and rotation
	//WeaponOffset.Z += 30.0f;
	//WeaponOffset.Y += 40.0f;
	//WeaponRotation.Yaw = -90.0f;
	WeaponOffset.Z += 40.0f;
	WeaponOffset.Y += 0.0f;
	WeaponOffset.X += -20.0f;
	WeaponRotation.Yaw = 0.0f;
}

// Called when the game starts or when spawned
void ABCharacter::BeginPlay()
{
	Super::BeginPlay();
	//SpawnWeapon(FWeaponInventoryItem());

	//Idle animation
	if (FirstPersonMesh != NULL && IdleAnimation != NULL)
	{
		//UAnimSequence != UAnimationAsset ???????
		FirstPersonMesh->PlayAnimation(IdleAnimation, true);
	}
}

// Called every frame
void ABCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (Weapon != NULL)
	{
		Weapon->SetActorLocation(GetActorLocation() + WeaponOffset);
		Weapon->SetActorRotation(GetActorRotation() + WeaponRotation);
	}
}

// Called to bind functionality to input
void ABCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


//Movements instructions
void ABCharacter::GoForward(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ABCharacter::GoRight(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ABCharacter::Turn(float value)
{
	AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABCharacter::LookUp(float value)
{
	AddControllerPitchInput(value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


//Weapon System
void ABCharacter::onFire()
{
	if (Weapon != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire pressed"));
		Weapon->StartFire();
	}
}

void ABCharacter::onStopFire()
{
	if (Weapon != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire released"));
		Weapon->EndFire();
	}
}

FVector ABCharacter::GetCameraLocation()
{
	return Weapon->WeaponVisual->GetSocketLocation("Muzzle");
}

FRotator ABCharacter::GetCameraRotation()
{
	return Weapon->WeaponVisual->GetSocketRotation("Muzzle");
}

void ABCharacter::traceLine(FHitResult & HitResult)
{
	//Debut du trace
	FVector CameraLoc = GetCameraLocation();
	FRotator CameraRot = GetCameraRotation();
	const FVector TraceDirection = CameraRot.Vector();
	//Portée
	const float TraceRange = 4096.0f;
	//Calcul EndPoint
	const FVector EndTrace = CameraLoc + TraceDirection * TraceRange;
	//Trace Query ?
	static FName FireTraceIdent = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(FireTraceIdent, true, this);
	TraceParams.bTraceAsyncScene = true;

	//LE TRACAGE
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		DrawDebugLine(World, CameraLoc, EndTrace, FColor(255, 0, 0), false, 0.2f, 0, 5);
		Weapon->currentAmmunitionInMagazine = Weapon->currentAmmunitionInMagazine - 1;
		this->updateAmmunitionAmountOnHUD(Weapon->currentAmmunitionInMagazine, Weapon->currentTotalAmmunition);
		World->LineTraceSingleByChannel(HitResult, CameraLoc, EndTrace, ECC_GameTraceChannel1, TraceParams);
	}
}

void ABCharacter::updateAmmunitionAmountOnHUD(uint8 AmmunitionInMagazine, uint8 AmmunitionInReserve)
{
	ABorderlandsPlayerController* PlayerController = Cast<ABorderlandsPlayerController>(GetController());
	if (PlayerController != NULL)
	{
		PlayerController->UpdateAmmunitionAmountOnHUD(AmmunitionInMagazine, AmmunitionInReserve);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find BorderlandsPlayerController instance"));
	}
}

void ABCharacter::UpdateHealthAmountOnHUD(bool HasHealthAmount, uint8 CurrentHealthAmount, uint8 MaximumHealthAmount)
{
	ABorderlandsPlayerController* PlayerController = Cast<ABorderlandsPlayerController>(GetController());
	if (PlayerController != NULL)
	{
		PlayerController->UpdateHealthAmountOnHUD(HasHealthAmount, CurrentHealthAmount, MaximumHealthAmount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find BorderlandsPlayerController instance"));
	}
}

void ABCharacter::SpawnWeapon(struct FWeaponInventoryItem WeaponInventoryItem)
{
	UWorld* World = GetWorld();
	//UE_LOG(LogTemp, Warning, TEXT("Appel SpawnWeapon()"));

	if (World != NULL)
	{
		if (Weapon != NULL)
		{
			Weapon->Destroy();
		}
		FVector NewLocation = GetActorLocation() + WeaponOffset;
		FRotator NewRotation = GetActorRotation() + WeaponRotation;
		Weapon = World->SpawnActor<AWeapon>(DefaultWeaponClass, NewLocation, NewRotation);
		if (Weapon == NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("Echec creation arme"));
		}
		else
		{
			Weapon->Owner = this;
			Weapon->FromInventoryItem(WeaponInventoryItem);
			Weapon->resupply();
			updateAmmunitionAmountOnHUD(Weapon->currentAmmunitionInMagazine, Weapon->currentTotalAmmunition);
			//Weapon->AttachRootComponentTo(CameraComponent, NAME_None, EAttachLocation::SnapToTarget);
		}
	}
}
