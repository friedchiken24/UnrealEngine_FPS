// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Interactable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

DECLARE_DELEGATE_ThreeParams(FOnUpdatePickupWidget, FString, EGunRarity, int)


UENUM(BlueprintType)
enum class EGunRarity : uint8
{
	Legendary UMETA(DisplayName = "Legendary"),
	Rare UMETA(DisplayName = "Rare"),
	Common UMETA(DisplayName = "Common")
};


UCLASS()
class UE_FPS_API AGun : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AGun();

protected:
	virtual void BeginPlay() override;

	////////////////////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly)
	class UWidgetComponent* PickupWidgetComponent;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* icon;

	class UPickupWidget* pickupWidget;

	// not good to use delegates with widget components
	FOnUpdatePickupWidget UpdatePickupWidget;

public:	
	virtual void Tick(float DeltaTime) override;

	void Interact() override;

	void Leave() override;

	void Click(AMainPlayer* player) override;

	////////////////////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly)
	int maxAmmo;

	int currentClipSize;

	UPROPERTY(EditDefaultsOnly)
	int maxClipSize;

	UPROPERTY(EditDefaultsOnly)
	int damage;

	UPROPERTY(EditDefaultsOnly)
	FString name;

	UPROPERTY(EditDefaultsOnly)
	EGunRarity gunRarity;

};