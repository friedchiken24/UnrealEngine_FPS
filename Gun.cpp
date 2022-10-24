// Fill out your copyright notice in the Description page of Project Settings.
#include "Gun.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "PickupWidget.h"


AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = Mesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	BoxCollider->SetupAttachment(RootComponent);

	PickupWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidgetComponent->SetupAttachment(RootComponent);
}


void AGun::BeginPlay()
{
	Super::BeginPlay();

	PickupWidgetComponent->SetVisibility(false);

	currentClipSize = maxClipSize;

	pickupWidget = Cast<UPickupWidget>(PickupWidgetComponent->GetUserWidgetObject());
}


void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGun::Interact()
{
	PickupWidgetComponent->SetVisibility(true);
	pickupWidget->UpdatePickupWidget(name, gunRarity, damage, icon);
}


void AGun::Leave()
{
	PickupWidgetComponent->SetVisibility(false);
}


void AGun::Click(AMainPlayer* player)
{
	player->EquipGun(this);
	player->OnAmmoCountChange.ExecuteIfBound(currentClipSize, maxAmmo);
	PickupWidgetComponent->SetVisibility(false);
	Destroy();
}