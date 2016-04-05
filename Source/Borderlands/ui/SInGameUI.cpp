// Fill out your copyright notice in the Description page of Project Settings.

#include "Borderlands.h"
#include "SInGameUI.h"
#include "SlateOptMacros.h"
#include "../BorderlandsHUD.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInGameUI::Construct(const FArguments& InArgs)
{
	BorderlandsHUD = InArgs._BorderlandsHUD;
	
	ChildSlot
	[
		SNew(SOverlay)
		//Ammunition counter
		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Right)
		[
			SNew(STextBlock)
			.ColorAndOpacity(FLinearColor::White)
			.ShadowColorAndOpacity(FLinearColor::Black)
			.ShadowOffset(FIntPoint(-1, 1))
			.Font(FSlateFontInfo("Arial", 26))
			.Text(this, &SInGameUI::GetAmmunitionText)
		]

		//Health/Shield/Armor Bar
		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Left)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.ColorAndOpacity(FLinearColor::White)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Arial", 26))
					.Text(FText::FromString("Health"))
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SBox)
					.WidthOverride(600.0f)
					[
						SNew(SProgressBar)
						.Visibility(this, &SInGameUI::HasHealthAbsorber)
						.BarFillType(EProgressBarFillType::LeftToRight)
						.FillColorAndOpacity(FLinearColor::Red)
						//.Percent(0.5f)
						.Percent(this, &SInGameUI::GetHealthPercentage)
					]
				]
			]
		]	
	];
	
	UE_LOG(LogTemp, Warning, TEXT("Construct"));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

EVisibility SInGameUI::HasHealthAbsorber() const
{
	if (BorderlandsHUD->HasHealthAbsorber)
	{
		return EVisibility::Visible;
	}
	return EVisibility::Collapsed;
}

FText SInGameUI::GetAmmunitionText() const
{
	FString AmmunitionText = FString::FromInt(BorderlandsHUD->AmmoInMagazine) + " / " + FString::FromInt(BorderlandsHUD->AmmoInReserve);
	return FText::FromString(AmmunitionText);
}

TOptional< float > SInGameUI::GetHealthPercentage() const
{
	if (HasHealthAbsorber() == EVisibility::Visible)
	{
		float res = BorderlandsHUD->CurrentHealthAmount / BorderlandsHUD->MaximumHealthAmount;
		return res;
	}
	return 0.f;
}
