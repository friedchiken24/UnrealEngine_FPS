// Fill out your copyright notice in the Description page of Project Settings.
#include "Shape.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Runtime/UMG/Public/UMG.h"


AShape::AShape()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = Mesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	BoxCollider->SetupAttachment(RootComponent);

	Audio = CreateDefaultSubobject<UAudioComponent>("Audio Source");
	Audio->SetupAttachment(RootComponent);

	health = 100;
}


void AShape::BeginPlay()
{
	Super::BeginPlay();

	Audio->PitchMultiplier = 2.0f;
}


void AShape::Damage(int amount)
{
	if (health - amount <= 0)
	{
		Audio->Play();
		Destroy();
	}
	else
	{
		health -= amount;
	}
}


int AShape::GetHealth()
{
	return health;
}


void AShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}