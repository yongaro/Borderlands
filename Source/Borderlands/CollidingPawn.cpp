// Fill out your copyright notice in the Description page of Project Settings.

#include "CollidingPawn.h"
#include "Borderlands.h"
#include "CollidingPawnMovementComponent.h"
#include "weapon/Weapon.h"
#include "weapon/RifleWeaponTypeComponent.h"


// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Our root component will be a sphere that reacts to physics
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Create and position a mesh component so we can see where our sphere is
	SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);// SphereVisual->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	// Create a particle system that we can activate or deactivate
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);// OurParticleSystem->AttachTo(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	// SpringArm->AttachTo(RootComponent);
	SpringArm->SetupAttachment(RootComponent);
	// SpringArm->AttachToComponent(RootComponent,
	                            //  {EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true});
	SpringArm->RelativeRotation = FRotator(-25.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// Create a camera and attach to our spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create an instance of our movement component, and tell it to update the root.
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		//Weapon = World->SpawnActor<AWeapon>(GetClass(), GetActorLocation(), FRotator::ZeroRotator); //ATTENTION CA CRASH AUSSI
		FVector NewLocation = GetActorLocation() + WeaponOffset;
		FRotator NewRotation = GetActorRotation() + WeaponRotation;
		Weapon = World->SpawnActor<AWeapon>(WeaponClass, NewLocation, NewRotation);
		if (Weapon == NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("No weapon available"));
		}
		else
		{
			//Weapon->Owner = this;
			//On modifie une valeur de l'arme, puis on la reset
			Weapon->MagazineSize = 30;
			Weapon->RateOfFire = 0.1f;
			Weapon->resupply();
			//On fait en sorte que notre arme soit automatique
			//Weapon->WeaponTypeComponent = CreateDefaultSubobject<URifleWeaponTypeComponent>(TEXT("RifleWeaponTypeComponent")); //-> ca crash
			UWeaponTypeComponent* NewWeaponTypeComponent = NewObject<URifleWeaponTypeComponent>(Weapon);
			if (NewWeaponTypeComponent != NULL)
			{
				NewWeaponTypeComponent->OuterWeapon = Weapon;
				NewWeaponTypeComponent->RegisterComponent();
				Weapon->WeaponTypeComponent->DestroyComponent();
				Weapon->WeaponTypeComponent = NewWeaponTypeComponent;
			}
			//Weapon->AttachRootComponentTo(SphereVisual, NAME_None, EAttachLocation::SnapToTarget);
		}
	}
}

// Called every frame
void ACollidingPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (Weapon != NULL)
	{
		Weapon->SetActorLocation(GetActorLocation() + WeaponOffset);
		Weapon->SetActorRotation(GetActorRotation() + WeaponRotation);
	}
}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ACollidingPawn::onFire);
	InputComponent->BindAction("Fire", IE_Released, this, &ACollidingPawn::onStopFire);

	InputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
}

UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void ACollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}

void ACollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisValue;
	SetActorRotation(NewRotation);
}

bool ACollidingPawn::IsFiringDisabled()
{
	return false;
}

void ACollidingPawn::onFire()
{
	if (Weapon != NULL)
	{
		Weapon->StartFire();
	}
}

void ACollidingPawn::onStopFire()
{
	if (Weapon != NULL)
	{
		Weapon->EndFire();
	}
}

FVector ACollidingPawn::GetCameraLocation()
{
	return Weapon->WeaponVisual->GetSocketLocation("Muzzle");
}

FRotator ACollidingPawn::GetCameraRotation()
{
	return Weapon->WeaponVisual->GetSocketRotation("Muzzle");
}

void ACollidingPawn::traceLine(FHitResult & HitResult)
{
	//Debut du trace
	FVector CameraLoc = GetCameraLocation();
	FRotator CameraRot = GetCameraRotation();
	const FVector TraceDirection = CameraRot.Vector();
	//Port�e
	const float TraceRange = 4096.0f;
	//Calcul EndPoint
	const FVector EndTrace = CameraLoc + TraceDirection * TraceRange;
	//Trace Query ? mdr je s� pa
	static FName FireTraceIdent = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams TraceParams(FireTraceIdent, true, this);
	// TraceParams.bTraceAsyncScene = true; // deprecated ? 

	//LE TRACAGE
	UWorld* World = GetWorld();
	if (World != NULL)
	{
		World->LineTraceSingleByChannel(HitResult, CameraLoc, EndTrace, ECC_GameTraceChannel1, TraceParams);
	}
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}
