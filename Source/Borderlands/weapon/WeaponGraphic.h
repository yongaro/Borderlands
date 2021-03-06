// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponGraphic.generated.h"

//Contient toutes les informations d une piece d arme et son manufacturer
USTRUCT()
struct FPart{
	GENERATED_USTRUCT_BODY()
	FString manufacturer;
	TMap<FString,FString> desc;
	FString getValue(FString key){ return desc[key]; }
};


//Definit l ensemble des pieces pour un type d arme
//Le but est de demander une partie de chaque collection pour constituer une arme de maniere procedurale
USTRUCT()
struct FWeaponsParts{
	GENERATED_USTRUCT_BODY()
	FString wtype;
	TArray<FPart*> bodies;
	TArray<FPart*> canons;
	TArray<FPart*> handles;
	TArray<FPart*> others;
	FPart* getRandom(FString category){
		if( category.Equals(FString("body"),ESearchCase::Type::IgnoreCase ) ){ return bodies[FMath::RandRange(0,bodies.Num()-1)]; }
		if( category.Equals(FString("canon"),ESearchCase::Type::IgnoreCase ) ){ return canons[FMath::RandRange(0,canons.Num()-1)]; }
		if( category.Equals(FString("handle"),ESearchCase::Type::IgnoreCase ) ){ return handles[FMath::RandRange(0,handles.Num()-1)]; }
		if( category.Equals(FString("other"),ESearchCase::Type::IgnoreCase ) ){ return others[FMath::RandRange(0,others.Num()-1)]; }
		
		UE_LOG(LogTemp, Warning,TEXT("FWeaponParts::getRandom -- Unknown category : %s"), *category);
		return NULL;
	}
	
	void Add(FPart* p,FString category){
		if( category.Equals(FString("body"),ESearchCase::Type::IgnoreCase ) ){ bodies.Add(p); }
		if( category.Equals(FString("canon"),ESearchCase::Type::IgnoreCase ) ){ canons.Add(p); }
		if( category.Equals(FString("handle"),ESearchCase::Type::IgnoreCase ) ){ handles.Add(p); }
		if( category.Equals(FString("other"),ESearchCase::Type::IgnoreCase ) ){ others.Add(p); }
	}	
};



UCLASS()
class BORDERLANDS_API AWeaponGraphic : public AActor{
	GENERATED_BODY()

public:	
	static TArray<FWeaponsParts*>* weaponsParts;
	
	TArray< class USkeletalMeshComponent* > meshes;
	TArray< FPart* > parts;
	class UAnimSequence* FPreloadAnim;
	class UAnimSequence* reloadAnim;
	class UAnimSequence* fireAnim;
	

	virtual void defaultWeap();
	virtual void bind();
	virtual void fire();
	virtual void reload();
	virtual void attachTo( AActor*, FName, EAttachLocation::Type, bool);
	virtual class USkeletalMeshComponent* getRoot();
	static void loadXML();
	static FWeaponsParts* getWtype(FString);
	
	
	// Sets default values for this actor's properties
	AWeaponGraphic();

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
