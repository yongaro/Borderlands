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
						.BarFillType(EProgressBarFillType::LeftToRight)
						.FillColorAndOpacity(FLinearColor::Red)
						.Percent(0.5f)
					]
				]
			]
		]	
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
