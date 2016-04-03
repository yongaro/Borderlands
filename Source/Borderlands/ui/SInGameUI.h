// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class BORDERLANDS_API SInGameUI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInGameUI)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class ABorderlandsHUD>, BorderlandsHUD)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	// Stores a weak reference to the HUD controlling this class.
	TWeakObjectPtr<class ABorderlandsHUD> BorderlandsHUD;

	//Predicates for absorber bars
	EVisibility HasHealthAbsorber() const;

	//Delegates methods for updates
	FText GetAmmunitionText() const;
	TOptional< float > GetHealthPercentage() const;
};
