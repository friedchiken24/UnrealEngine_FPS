// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPlayer.h"
#include "Damageable.h"
#include "Components/CapsuleComponent.h"
#include "Gun.h"
#include "Interactable.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"


AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FPSCameraComponent->bUsePawnControlRotation = true;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(FPSCameraComponent);
}


void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionProfileName("Player");

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayer::OnEnemyTriggerEnter);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayer::OnGunTriggerEnter);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainPlayer::OnGunTriggerExit);

	GunMesh->SetVisibility(false);
}


void AMainPlayer::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}


void AMainPlayer::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}


void AMainPlayer::LookUp(float value)
{
	AddControllerPitchInput(-value * 110 * GetWorld()->GetDeltaSeconds());
}


void AMainPlayer::LookRight(float value)
{
	AddControllerYawInput(value * 110 * GetWorld()->GetDeltaSeconds());
}


void AMainPlayer::Shoot()
{
	if (gun == nullptr) return;

	FVector start = GetActorLocation();
	FVector forward = GetActorForwardVector();
	FVector end = start + (forward * 5000.0f);

	FHitResult hit;

	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_GameTraceChannel2, collisionParams))
	{
		IDamageable* obj = Cast<IDamageable>(hit.GetActor());

		if (obj)
		{
			obj->Damage(gun->damage);
			gun->currentClipSize--;
			OnAmmoCountChange.ExecuteIfBound(gun->currentClipSize, gun->maxAmmo);
		}
	}
	else
	{
		gun->currentClipSize--;
		OnAmmoCountChange.ExecuteIfBound(gun->currentClipSize, gun->maxAmmo);
	}
}


void AMainPlayer::OnGunTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	interactable = Cast<IInteractable>(OtherActor);

	if (interactable)
	{
		interactable->Interact();

		//OnAmmoCountChange.ExecuteIfBound(gun->maxClipSize, gun->maxAmmo);
	}
}


void AMainPlayer::OnGunTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (interactable)
	{
		interactable->Leave();
		interactable = nullptr;
	}
}


void AMainPlayer::OnEnemyTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageable* obj = Cast<IDamageable>(OtherActor);

	if (obj)
	{
		
	}
}


void AMainPlayer::ClickOnInteractable()
{
	if (interactable)
	{
		interactable->Click(this);
	}
}


void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainPlayer::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AMainPlayer::LookRight);

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AMainPlayer::Shoot);
	PlayerInputComponent->BindAction("ClickOnInteractable", EInputEvent::IE_Pressed, this, &AMainPlayer::ClickOnInteractable);
}


void AMainPlayer::EquipGun(AGun* obj)
{
	GunMesh->SetVisibility(true);
	gun = obj;
}