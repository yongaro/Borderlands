// Fill out your copyright notice in the Description page of Project Settings.

#include "FPTest.h"
#include "Borderlands.h"
#include "../weapon/WeaponGraphic.h"



// Sets default values
AFPTest::AFPTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	//Corps
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/Borderlands/characters/claptrap/FP/Skel_FragTrap_Arms.Skel_FragTrap_Arms'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/Borderlands/characters/claptrap/FP/FragtrapWheelArm_Dif_Mat.FragtrapWheelArm_Dif_Mat'"));
	MeshComp->SetSkeletalMesh(MeshObj.Object);
	MeshComp->SetMaterial(0, MeshMaterial.Object);
	
	const ConstructorHelpers::FObjectFinder<UAnimSequence> FUU(TEXT("AnimSequence'/Game/Borderlands/characters/claptrap/FP/AnimSet/1st_Person_Pistol/Idle_Anim.Idle_Anim'"));
	Anime = FUU.Object;
}

// Called when the game starts or when spawned
void AFPTest::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->PlayAnimation(Anime,true);
	
}

// Called every frame
void AFPTest::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFPTest::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

