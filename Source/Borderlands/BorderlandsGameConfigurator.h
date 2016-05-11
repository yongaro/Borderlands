// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BorderlandsGameConfigurator.generated.h"

/**
 * 
 */
UCLASS()
class BORDERLANDS_API UBorderlandsGameConfigurator : public UObject
{
	GENERATED_BODY()
	
public:
	UBorderlandsGameConfigurator();
	~UBorderlandsGameConfigurator();
	
	//Liste de features
	bool LoadFeaturesFromFile(FString path);
	bool HasFeature(FString feature);
	uint32 GetFeaturesCount();
	
	//Configuration
	void ConfigureGame();

protected:
	TArray<FString> features;
};
