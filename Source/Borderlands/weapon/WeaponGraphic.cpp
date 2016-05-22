// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "XmlParser.h"
#include "WeaponGraphic.h"

TArray<FWeaponsParts*>* AWeaponGraphic::weaponsParts = NULL;


void AWeaponGraphic::defaultWeap(){
	AWeaponGraphic::loadXML();
	FWeaponsParts* pistols = AWeaponGraphic::getWtype(FString("pistols"));
	FPart* gunBodyP = pistols->getRandom(FString("body"));
	FPart* gunCanonP = pistols->getRandom(FString("canon"));
	FPart* gunHandleP = pistols->getRandom(FString("handle"));
	FPart* gunOtherP = pistols->getRandom(FString("other"));
 
	parts.Add(gunBodyP);
	parts.Add(gunCanonP);
	parts.Add(gunHandleP);
	
	//Recherche des skeletal mesh pour les differentes parties
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunBMeshObj( *(gunBodyP->getValue(FString("mesh"))) );
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunCMeshObj( *(gunCanonP->getValue(FString("mesh"))) );
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunHMeshObj( *(gunHandleP->getValue(FString("mesh"))) );
	
	//Recherche des materiaux de chaque partie
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunBMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Black.M_LightSculpture_Black'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunCMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Blue.M_LightSculpture_Blue'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunHMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Orange.M_LightSculpture_Orange'"));
	const ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> gunOMaterial(TEXT("MaterialInstanceConstant'/Game/DemoRoom/Materials/M_LightSculpture_Red.M_LightSculpture_Red'"));
	
	//Animation de tir
	const ConstructorHelpers::FObjectFinder<UAnimSequence> fireAss(*(gunBodyP->getValue(FString("fireAnim"))));
	fireAnim = fireAss.Object;
	
	//Animation de recharge
	const ConstructorHelpers::FObjectFinder<UAnimSequence> reloadAss( *(gunBodyP->getValue(FString("reloadAnim"))) );
	reloadAnim = reloadAss.Object;

	//Animation de recharge du personnage
	const ConstructorHelpers::FObjectFinder<UAnimSequence> FPreloadAss( *(gunBodyP->getValue(FString("FPreloadAnim"))) );
	FPreloadAnim = FPreloadAss.Object;	
	
	//Creation des composants
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("gunRoot"));
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunBMesh")));
	meshes.Last()->SetSkeletalMesh(gunBMeshObj.Object); meshes.Last()->SetMaterial(0, gunBMaterial.Object);
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunCMesh"))); 
	meshes.Last()->SetSkeletalMesh(gunCMeshObj.Object); meshes.Last()->SetMaterial(0, gunCMaterial.Object);
	
	meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunHMesh"))); 
	meshes.Last()->SetSkeletalMesh(gunHMeshObj.Object); meshes.Last()->SetMaterial(0, gunHMaterial.Object);
	
	if(FMath::RandBool() ){
		const ConstructorHelpers::FObjectFinder<USkeletalMesh> gunOMeshObj( *(gunOtherP->getValue(FString("mesh"))) );
		meshes.Add(CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gunOMesh"))); 
		meshes.Last()->SetSkeletalMesh(gunOMeshObj.Object); meshes.Last()->SetMaterial(0, gunOMaterial.Object);
		parts.Add(gunOtherP);
	}
	
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
		
		if ( file->IsValid() ){
			FXmlNode* root = file->GetRootNode();
			if( root != nullptr ){
				TArray<FXmlNode*> weaponTypes = root->GetChildrenNodes();
				for( FXmlNode* weaponType : weaponTypes ){
					
					//UE_LOG(LogTemp, Warning,TEXT("%s"), *(weaponType->GetAttribute(FString("value"))) );
					collection = AWeaponGraphic::getWtype( weaponType->GetAttribute(FString("value")) );
					TArray<FXmlNode*> categories = weaponType->GetChildrenNodes();
					for( FXmlNode* category : categories ){
						
						//UE_LOG(LogTemp, Warning,TEXT("	%s"), *(category->GetAttribute(FString("value"))) );
						cat = category->GetAttribute(FString("value"));
						TArray<FXmlNode*> parts = category->GetChildrenNodes();
						for( FXmlNode* part : parts ){
							
							//UE_LOG(LogTemp, Warning,TEXT("		%s"), *(part->GetAttribute(FString("manufacturer"))) );
							cur = new FPart();
							cur->manufacturer = part->GetAttribute(FString("manufacturer"));
							TArray<FXmlNode*> descs = part->GetChildrenNodes()[0]->GetChildrenNodes();
							for( FXmlNode* d : descs ){
								//UE_LOG(LogTemp, Warning,TEXT("%s -- %s"), *(d->GetAttribute(FString("name"))), *(d->GetAttribute(FString("value"))) );
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

