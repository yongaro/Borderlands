// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "XmlParser.h"
#include "WeaponGraphic.h"

TArray<FWeaponsParts*>* AWeaponGraphic::weaponsParts = NULL;


void AWeaponGraphic::defaultWeap(){
	AWeaponGraphic::loadXML();
//	FWeaponsParts* pistols = AWeaponGraphic::getWtype(FString("pistols"));
//	FPart* gunBodyP = pistols->getRandom(FString("body"));
//	FPart* gunCanonP = pistols->getRandom(FString("canon"));
//	FPart* gunHandleP = pistols->getRandom(FString("handle"));
 
	
	//if(gunBodyP != NULL){ UE_LOG(LogTemp, Warning,TEXT("C PA VIDE POURTAN %s"),  TEXT(gunBodyP->getValue(FString("mesh"))) ); }
	//if(gunCanonP != NULL){ UE_LOG(LogTemp, Warning,TEXT("C PA VIDE POURTAN")); }
	//if(gunHandleP != NULL){ UE_LOG(LogTemp, Warning,TEXT("C PA VIDE POURTAN")); }
	//Recherche des skeletal mesh pour les differentes parties
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunBMeshObj(TEXT("SkeletalMesh'/Game/Borderlands/weapons/pistols/body_bandit.body_bandit'"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunCMeshObj(TEXT("SkeletalMesh'/Game/Borderlands/weapons/pistols/canon_jakobs.canon_jakobs'"));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunHMeshObj(TEXT("SkeletalMesh'/Game/Borderlands/weapons/pistols/handle_jakobs.handle_jakobs'"));
	//const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunBMeshObj( *(gunBodyP->getValue(FString("mesh"))) );
	//const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunCMeshObj( *(gunCanonP->getValue(FString("mesh"))) );
	//const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunHMeshObj( *(gunHandleP->getValue(FString("mesh"))) );
	
	//Recherche des materiaux de chaque partie
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunBMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_DemoWall_Inst_3.M_DemoWall_Inst_3'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunCMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Red.M_LightSculpture_Red'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunHMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Green.M_LightSculpture_Green'"));
	
	//Animation de tir
	const ConstructorHelpers::FObjectFinder<UAnimSequence> fireAss(TEXT("AnimSequence'/Game/Borderlands/weapons/pistols/AnimSet/fire__auto.fire__auto'"));
	fireAnim = fireAss.Object;
	
	//Animation de recharge
	const ConstructorHelpers::FObjectFinder<UAnimSequence> reloadAss(TEXT("AnimSequence'/Game/Borderlands/weapons/pistols/AnimSet/fire__auto.fire__auto'"));
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

void AWeaponGraphic::loadXML(){
	if( AWeaponGraphic::weaponsParts == NULL ){ 
		AWeaponGraphic::weaponsParts = new TArray<FWeaponsParts*>( );
		/*Lecture d'un fichier XML*/
		FString pathToFile = FPaths::GameContentDir(); pathToFile+="Borderlands/weapons/weapons.xml";
		FXmlFile *file = new FXmlFile(pathToFile);

		FWeaponsParts* collection = NULL;
		FString cat;
		FPart* cur = NULL;
		FString fu;
		FString bar;
		
		if ( file->IsValid() ){
			FXmlNode* root = file->GetRootNode();
			if( root != nullptr ){
				TArray<FXmlNode*> weaponTypes = root->GetChildrenNodes();
				for( FXmlNode* weaponType : weaponTypes ){
					
					collection = AWeaponGraphic::getWtype( weaponType->GetAttribute(FString("value")) );
					TArray<FXmlNode*> categories = weaponType->GetChildrenNodes();
					for( FXmlNode* category : categories ){
						
						cat = category->GetAttribute(FString("value"));
						TArray<FXmlNode*> parts = category->GetChildrenNodes();
						for( FXmlNode* part : parts ){
							
							cur = new FPart();
							cur->manufacturer = part->GetAttribute(FString("manufacturer"));
							TArray<FXmlNode*> descs = part->GetChildrenNodes();
							for( FXmlNode* d : descs ){
								//fu = d->GetAttribute(FString("name")); bar = d->GetAttribute(FString("value"));
								//UE_LOG(LogTemp, Warning,TEXT("%s"), *(d->GetAttribute(FString("name")))   );
								cur->desc.Add( d->GetAttribute(FString("name")),d->GetAttribute(FString("value")) );
							}
							collection->Add(cur,cat);	
						}
					}
				}
			}
			else{
				UE_LOG(LogTemp, Warning, TEXT("No root"));
			}
		}
		else{
			UE_LOG(LogTemp, Warning,TEXT("Fichier introuvable : %s"), *pathToFile);
		}
	}
}

FWeaponsParts* AWeaponGraphic::getWtype(FString wt){
	for( FWeaponsParts* fwp : *AWeaponGraphic::weaponsParts ){		
		if( fwp->wtype.Equals(wt,ESearchCase::Type::IgnoreCase) ){ return fwp; }
	}
	
	FWeaponsParts* res = new FWeaponsParts();
	res->wtype = wt;
	AWeaponGraphic::weaponsParts->Add( res );	
	return res;
}

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

