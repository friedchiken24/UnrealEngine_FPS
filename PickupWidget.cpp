// Fill out your copyright notice in the Description page of Project Settings.
#include "PickupWidget.h"
#include "Components/TextBlock.h"
#include "MainPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameState.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"


void UPickupWidget::NativeOnInitialized()
{
	player = Cast<AMainPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	mainGameState = Cast<AMainGameState>(UGameplayStatics::GetGameState(GetWorld()));
}


void UPickupWidget::UpdatePickupWidget(FString weaponName, EGunRarity gunRarity, int damage, UTexture2D* icon)
{
	text_weaponName->SetText(FText::FromString(weaponName));
	//text_weaponName->SetText(FText::FromString(mainGameState->dumbName));

	//const TEnumAsByte<EGunRarity> SurfaceEnum = gunRarity;
	//FString EnumAsString = UEnum::GetValueAsString(SurfaceEnum.GetValue());
	//text_weaponRarity->SetText(FText::FromString(EnumAsString));

	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGunRarity"), true);
	FString EnumAsString = EnumPtr->GetEnumName((int32)gunRarity);
	text_weaponRarity->SetText(FText::FromString(EnumAsString));

	text_weaponDamage->SetText(FText::AsNumber(damage));

	image_weaponIcon->SetBrushFromTexture(icon);
}