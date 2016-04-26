// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "WeapGraphicComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BORDERLANDS_API UWeapGraphicComp : public UActorComponent
{
	GENERATED_BODY()

	static unsigned int cpt;
	
	TArray< class USkeletalMeshComponent* > meshes;
	class UAnimSequence* reloadAnim;
	class UAnimSequence* fireAnim;
public:	
	virtual void defaultWeap();
	virtual void bind();
	virtual void fire();
	virtual void reload();
	
	// Sets default values for this component's properties
	UWeapGraphicComp();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
