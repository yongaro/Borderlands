// Fill out your copyright notice in the Description page of Project Settings.

#include "BCharacter.h"
#include "Borderlands.h"
#include "../weapon/Weapon.h"
#include "../weapon/WeaponTypeComponent.h"
#include "../weapon/RifleWeaponTypeComponent.h"
#include "../DamageHandler.h"
#include "BorderlandsPlayerController.h"
#include "Animation/AnimSingleNodeInstance.h"

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
	// CameraComponent->AttachParent = GetCapsuleComponent();
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	CameraComponent->bUsePawnControlRotation = true;

	//First person mesh
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	// FirstPersonMesh->AttachParent = CameraComponent;
	FirstPersonMesh->SetupAttachment(CameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;

	//First person skeletal mesh asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> FirstPersonMeshAsset(TEXT("SkeletalMesh'/Game/Borderlands/characters/claptrap/FP/Skel_FragTrap_Arms.Skel_FragTrap_Arms'"));
	const ConstructorHelpers::FObjectFinder<UMaterial> FPMat(TEXT("Material'/Game/Borderlands/characters/claptrap/FP/FragtrapWheelArm_Dif_Mat.FragtrapWheelArm_Dif_Mat'"));
	if (FirstPersonMeshAsset.Succeeded())
	{
		FirstPersonMesh->SetSkeletalMesh(FirstPersonMeshAsset.Object);
		FirstPersonMesh->SetMaterial(0, FPMat.Object);
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
		if(Weapon != NULL){
			//Weapon->AttachRootComponentToActor(this,TEXT("R_Weapon_Bone"),EAttachLocation::SnapToTargetIncludingScale,true);
			Weapon->GetRootComponent()->AttachToComponent(FirstPersonMesh,
			                                             {EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true},
			                                             TEXT("R_Weapon_Bone"));
		}
	}
}

// Called every frame
void ABCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent){
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
		Weapon->StartFire();
	}
}

void ABCharacter::onStopFire()
{
	if (Weapon != NULL)
	{
		Weapon->EndFire();
	}
}

void ABCharacter::BeginReload()
{
	//On ne tire pas pendant le rechargement
	bIsFiringDisabled = true;

	//Recharge ...
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		if (Weapon != NULL && Weapon->currentTotalAmmunition > 0) {
			Weapon->reload();
			FirstPersonMesh->PlayAnimation(Weapon->WVisual->FPreloadAnim, false);
			float animLen = FirstPersonMesh->GetSingleNodeInstance()->GetLength();
			FTimerHandle timerHandler;
			GetWorldTimerManager().SetTimer(timerHandler, this, &ABCharacter::EndReload, animLen, false);
		}
	}
}

void ABCharacter::EndReload()
{
	if (Weapon != NULL)
	{
		uint8 ammoReloaded = FMath::Min(Weapon->currentTotalAmmunition, (uint8) (Weapon->MagazineSize - Weapon->currentAmmunitionInMagazine));
		Weapon->currentAmmunitionInMagazine += ammoReloaded;
		Weapon->currentTotalAmmunition -= ammoReloaded;
	}
	bIsFiringDisabled = false;
	updateAmmunitionAmountOnHUD(Weapon->currentAmmunitionInMagazine, Weapon->currentTotalAmmunition);
}

FVector ABCharacter::GetCameraLocation()
{
	FMinimalViewInfo viewInfo;
	CameraComponent->GetCameraView(0.f, viewInfo);
	return viewInfo.Location;
}

FRotator ABCharacter::GetCameraRotation()
{
	FMinimalViewInfo viewInfo;
	CameraComponent->GetCameraView(0.f, viewInfo);
	return viewInfo.Rotation;
}

void ABCharacter::traceLine(FHitResult & HitResult)
{
	//Debut du trace
	FVector CameraLoc = GetCameraLocation();
	FRotator CameraRot = GetCameraRotation();
	const FVector TraceDirection = CameraRot.Vector();
	//Port�e
	const float TraceRange = 4096.0f;
	//Calcul EndPoint
	const FVector EndTrace = CameraLoc + TraceDirection * TraceRange;
	//Trace Query ?
	static FName FireTraceIdent = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(FireTraceIdent, true, this);
	// TraceParams.bTraceAsyncScene = true;

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

void ABCharacter::UpdateShieldAmountOnHUD(bool HasShieldAmount, uint8 CurrentShieldAmount, uint8 MaximumShieldAmount)
{
	ABorderlandsPlayerController* PlayerController = Cast<ABorderlandsPlayerController>(GetController());
	if (PlayerController != NULL)
	{
		PlayerController->UpdateShieldAmountOnHUD(HasShieldAmount, CurrentShieldAmount, MaximumShieldAmount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find BorderlandsPlayerController instance"));
	}
}

void ABCharacter::UpdateArmorAmountOnHUD(bool HasArmorAmount, uint8 CurrentArmorAmount, uint8 MaximumArmorAmount)
{
	ABorderlandsPlayerController* PlayerController = Cast<ABorderlandsPlayerController>(GetController());
	if (PlayerController != NULL)
	{
		PlayerController->UpdateArmorAmountOnHUD(HasArmorAmount, CurrentArmorAmount, MaximumArmorAmount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot find BorderlandsPlayerController instance"));
	}
}

void ABCharacter::SpawnWeapon(struct FWeaponInventoryItem WeaponInventoryItem)
{
	UWorld* World = GetWorld();

	if (World != NULL)
	{
		if (Weapon != NULL)
		{
			Weapon->DestroyWeapon();
		}
		FVector NewLocation = GetActorLocation() + WeaponOffset;
		FRotator NewRotation = GetActorRotation() + WeaponRotation;
		Weapon = World->SpawnActor<AWeapon>(DefaultWeaponClass, NewLocation, NewRotation);
		if (Weapon == NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to create the weapon"));
		}
		else
		{
			Weapon->Owner = this;
			Weapon->FromInventoryItem(WeaponInventoryItem);
			Weapon->resupply();
			updateAmmunitionAmountOnHUD(Weapon->currentAmmunitionInMagazine, Weapon->currentTotalAmmunition);
			//Weapon->AttachRootComponentTo(CameraComponent, NAME_None, EAttachLocation::SnapToTarget);
			Weapon->GetRootComponent()->AttachToComponent(FirstPersonMesh,
			                                              {EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true},
			                                              TEXT("R_Weapon_Bone"));
		}
	}
}

float ABCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser){
	/*Test pour type de degats*/
	if (DamageHandler) {
		return DamageHandler->Execute_Damage(DamageHandler, DamageAmount, DamageEvent);
	}
	return 0.0f;
}




void ABCharacter::Connect(UActorComponent * comp)
{
	//DamageHandler ?
	auto damageHandler = Cast<UDamageHandler>(comp);
	if (damageHandler != nullptr)
	{
		damageHandler->OuterActor = this;
		if (!damageHandler->IsRegistered())
		{
			damageHandler->RegisterComponent();
		}
		if (DamageHandler != nullptr)
		{
			DamageHandler->DestroyComponent();
		}
		DamageHandler = damageHandler;
	}
}
