// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Damageable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shape.generated.h"

UCLASS()
class UE_FPS_API AShape : public AActor, public IDamageable
{
	GENERATED_BODY()
	
public:	
	AShape();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly)
	class UAudioComponent* Audio;

	void Damage(int amount) override;

	int GetHealth() override;

	///////////////////////////////////////////

	int health;

public:	
	virtual void Tick(float DeltaTime) override;

};