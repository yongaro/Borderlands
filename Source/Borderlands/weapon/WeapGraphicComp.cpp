// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "WeapGraphicComp.h"


void  UWeapGraphicComp::defaultWeap(){
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
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunRoot"))); 
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunBMesh"))); 
	meshes.Last()->SetSkeletalMesh(gunBMeshObj.Object); meshes.Last()->SetMaterial(0, gunBMaterial.Object);
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunCMesh"))); 
	meshes.Last()->SetSkeletalMesh(gunCMeshObj.Object); meshes.Last()->SetMaterial(0, gunCMaterial.Object);
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunHMesh"))); 
	meshes.Last()->SetSkeletalMesh(gunHMeshObj.Object); meshes.Last()->SetMaterial(0, gunHMaterial.Object);
}


void  UWeapGraphicComp::bind(){
	if( meshes.Num() > 2 ){
		for(size_t i = 1; i != meshes.Num(); ++i){
			meshes[i]->AttachTo( meshes[0], TEXT("Root"), EAttachLocation::SnapToTargetIncludingScale, true);
		}
	}
}

void  UWeapGraphicComp::fire(){
	if( meshes.Num() > 2 ){
		for(size_t i = 1; i != meshes.Num(); ++i){
			meshes[i]->PlayAnimation(fireAnim,false);
		}
	}
}

void  UWeapGraphicComp::reload(){
	if( meshes.Num() > 2 ){
		for(size_t i = 1; i != meshes.Num(); ++i){
			meshes[i]->PlayAnimation(reloadAnim,false);
		}
	}
}

// Sets default values for this component's properties
UWeapGraphicComp::UWeapGraphicComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeapGraphicComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeapGraphicComp::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

