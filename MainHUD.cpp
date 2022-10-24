// Fill out your copyright notice in the Description page of Project Settings.
#include "MainHUD.h"
#include "PlayerHUDUserWidget.h"


void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (BP_AmmoCountWidget)
	{
		PlayerHUD = CreateWidget<UPlayerHUDUserWidget>(GetWorld(), BP_AmmoCountWidget);

		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
			PlayerHUD->SetVisibility(ESlateVisibility::Visible);
		}
	}
}


void AMainHUD::DrawHUD()
{

}