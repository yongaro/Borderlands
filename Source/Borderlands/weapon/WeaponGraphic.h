// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponGraphic.generated.h"

UCLASS()
class BORDERLANDS_API AWeaponGraphic : public AActor{
	GENERATED_BODY()
	
	TArray< class USkeletalMeshComponent* > meshes;
	class UAnimSequence* reloadAnim;
	class UAnimSequence* fireAnim;
	
public:	
	virtual void defaultWeap();
	virtual void bind();
	virtual void fire();
	virtual void reload();
	virtual void attachTo( AActor*, FName, EAttachLocation::Type, bool);
	virtual class USkeletalMeshComponent* getRoot();
	
	
	// Sets default values for this actor's properties
	AWeaponGraphic();

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
