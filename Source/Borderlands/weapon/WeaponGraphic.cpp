// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "WeaponGraphic.h"



void AWeaponGraphic::defaultWeap(){
	//Recherche des skeletal mesh pour les differentes parties
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunBMeshObj(TEXT("SkeletalMesh'/Game/Borderlands/weapons/body_bandit.body_bandit'"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunCMeshObj(TEXT("SkeletalMesh'/Game/Borderlands/weapons/canon_jakobs.canon_jakobs'"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunHMeshObj(TEXT("SkeletalMesh'/Game/Borderlands/weapons/handle_jakobs.handle_jakobs'"));
	
	//Recherche des materiaux de chaque partie
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunBMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_DemoWall_Inst_3.M_DemoWall_Inst_3'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunCMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Red.M_LightSculpture_Red'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunHMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Green.M_LightSculpture_Green'"));
	
	//Animation de tir
	const ConstructorHelpers::FObjectFinder<UAnimSequence> fireAss(TEXT("AnimSequence'/Game/Borderlands/weapons/AnimSet/fire_auto.fire_auto'"));
	fireAnim = fireAss.Object;
	
	//Animation de recharge
	const ConstructorHelpers::FObjectFinder<UAnimSequence> reloadAss(TEXT("AnimSequence'/Game/Borderlands/weapons/AnimSet/fire_auto.fire_auto'"));
	reloadAnim = reloadAss.Object;

	//Creation des composants
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("gunRoot"));
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunBMesh")));
	meshes.Last()->SetSkeletalMesh(gunBMeshObj.Object); meshes.Last()->SetMaterial(0, gunBMaterial.Object);
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunCMesh"))); 
	meshes.Last()->SetSkeletalMesh(gunCMeshObj.Object); meshes.Last()->SetMaterial(0, gunCMaterial.Object);
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunHMesh"))); 
	meshes.Last()->SetSkeletalMesh(gunHMeshObj.Object); meshes.Last()->SetMaterial(0, gunHMaterial.Object);
}


void AWeaponGraphic::bind(){
	if( meshes.Num() > 2 ){
		for(size_t i = 0; i != meshes.Num(); ++i){
			meshes[i]->AttachTo( RootComponent, TEXT("Root"), EAttachLocation::SnapToTargetIncludingScale, true);
		}
	}
}

void AWeaponGraphic::fire(){
	if( meshes.Num() > 2 ){
		for(size_t i = 0; i != meshes.Num(); ++i){
			meshes[i]->PlayAnimation(fireAnim,false);
		}
	}
}

void AWeaponGraphic::reload(){
	if( meshes.Num() > 2 ){
		for(size_t i = 0; i != meshes.Num(); ++i){
			meshes[i]->PlayAnimation(reloadAnim,false);
		}
	}
}

void AWeaponGraphic::attachTo( AActor* actor, FName socket, EAttachLocation::Type location, bool bWeldSimulatedBodies){
	AttachRootComponentToActor(actor,socket,location,bWeldSimulatedBodies);
}

USkeletalMeshComponent* AWeaponGraphic::getRoot(){ return meshes[0]; }


// Sets default values
AWeaponGraphic::AWeaponGraphic(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	defaultWeap();
	bind();
	

}

// Called when the game starts or when spawned
void AWeaponGraphic::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void AWeaponGraphic::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
}

