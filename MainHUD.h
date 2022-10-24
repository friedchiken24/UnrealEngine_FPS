// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE_FPS_API AMainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> BP_AmmoCountWidget;

	class UPlayerHUDUserWidget* PlayerHUD;
	
};