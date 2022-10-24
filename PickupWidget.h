// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Gun.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupWidget.generated.h"


UCLASS()
class UE_FPS_API UPickupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdatePickupWidget(FString weaponName, EGunRarity gunRarity, int damage, UTexture2D* icon);
	
protected:
	virtual void NativeOnInitialized() override;

	///////////////////////////////////////////////////

	class AMainPlayer* player;

	class AMainGameState* mainGameState;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* text_weaponName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* text_weaponRarity;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* text_weaponDamage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* image_weaponIcon;

};