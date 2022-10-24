// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "MainPlayer.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class UE_FPS_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact() = 0;
	virtual void Leave() = 0;
	virtual void Click(AMainPlayer* player) = 0;

};