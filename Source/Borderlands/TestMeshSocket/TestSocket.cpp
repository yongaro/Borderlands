// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "TestSocket.h"
#include "Runtime/Engine/Classes/Animation/AnimSequence.h"

// Sets default values
ATestSocket::ATestSocket()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	 //Corps du personnage
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MyPawnMesh"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("SkeletalMesh'/Game/Borderlands/characters/claptrap/TP/Skel_FragTrap.Skel_FragTrap'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/Borderlands/characters/claptrap/TP/FragtrapWheelArm_Dif_Mat.FragtrapWheelArm_Dif_Mat'"));
	MeshComp->SetSkeletalMesh(MeshObj.Object);
	MeshComp->SetMaterial(0, MeshMaterial.Object);
  
	//Tete du personnage
	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MyPawnHeadMesh"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> HeadMeshObj(TEXT("SkeletalMesh'/Game/Borderlands/characters/claptrap/TP/heads/Che_GuevaTrap.Che_GuevaTrap'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> HeadMeshMaterial(TEXT("Material'/Game/Borderlands/characters/claptrap/TP/heads/Prototype009_Mat.Prototype009_Mat'"));
	HeadMesh->SetSkeletalMesh(HeadMeshObj.Object);
	HeadMesh->SetMaterial(0, HeadMeshMaterial.Object);

	
	MeshComp->AttachTo(HeadMesh, TEXT("Head"), EAttachLocation::SnapToTargetIncludingScale, true);
	const ConstructorHelpers::FObjectFinder<UAnimSequence> FUU(TEXT("AnimSequence'/Game/Borderlands/characters/claptrap/TP/AnimSet/Anim_Prototype_Skills/antic_dance_var5_Anim.antic_dance_var5_Anim'"));
	Anime = FUU.Object;
}

// Called when the game starts or when spawned
void ATestSocket::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->PlayAnimation(Anime,true);
	HeadMesh->PlayAnimation(Anime,true);
}

// Called every frame
void ATestSocket::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ATestSocket::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

