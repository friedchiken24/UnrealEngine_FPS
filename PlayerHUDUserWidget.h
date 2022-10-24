// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDUserWidget.generated.h"


UCLASS()
class UE_FPS_API UPlayerHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* text_currentAmmoCount;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* text_stockAmmoCount;

	class AMainPlayer* player;

public:
	void SetCurrentAmmoCountText(int currentAmmo, int stockAmmo);

};