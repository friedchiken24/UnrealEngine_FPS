#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

DECLARE_DELEGATE_TwoParams(FOnAmmoCountChange, int, int)

UCLASS()
class UE_FPS_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AMainPlayer();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void LookUp(float value);
	void LookRight(float value);

	void Shoot();

	UFUNCTION()
	void OnGunTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnGunTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnEnemyTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ClickOnInteractable();

	////////////////////////////////////////////////////////////////////

	class IInteractable* interactable;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* FPSCameraComponent;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EquipGun(class AGun* gun);

	////////////////////////////////////////////////////////////

	FOnAmmoCountChange OnAmmoCountChange;

	class AGun* gun;

};