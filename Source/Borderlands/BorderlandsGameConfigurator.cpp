// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "BorderlandsGameConfigurator.h"

UBorderlandsGameConfigurator::UBorderlandsGameConfigurator()
{
	//Default values ...
}

UBorderlandsGameConfigurator::~UBorderlandsGameConfigurator()
{

}

bool UBorderlandsGameConfigurator::LoadFeaturesFromFile(FString path)
{
	FString GameDir = FPaths::GameDir();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GameDir);
	FString FileData = "";
	FString CompleteFilePath = GameDir + "default.config";

	FFileHelper::LoadFileToString(FileData, *CompleteFilePath);
	//UE_LOG(LogTemp, Warning, TEXT("FileData : \"%s\""), *FileData);
	if (FileData == "")
	{
		return false;
	}

	FileData.ParseIntoArrayLines(features, true);
	for (auto& str : features)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	return true;
}

bool UBorderlandsGameConfigurator::HasFeature(FString feature)
{
	return features.Contains(feature);
}

uint32 UBorderlandsGameConfigurator::GetFeaturesCount()
{
	return features.Num();
}
