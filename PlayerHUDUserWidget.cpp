// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerHUDUserWidget.h"
#include "Components/TextBlock.h"
#include "MainPlayer.h"
#include "Kismet/GameplayStatics.h"


void UPlayerHUDUserWidget::NativeOnInitialized()
{
	player = Cast<AMainPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->OnAmmoCountChange.BindUObject(this, &UPlayerHUDUserWidget::SetCurrentAmmoCountText);
}


void UPlayerHUDUserWidget::SetCurrentAmmoCountText(int currentAmmo, int stockAmmo)
{
	text_currentAmmoCount->SetText(FText::AsNumber(currentAmmo));
	text_stockAmmoCount->SetText(FText::AsNumber(stockAmmo));
}