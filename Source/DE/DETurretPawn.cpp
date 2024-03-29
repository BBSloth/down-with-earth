// Fill out your copyright notice in the Description page of Project Settings.


#include "DETurretPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADETurretPawn::ADETurretPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBase = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Base"));
	SetRootComponent(TurretBase);

	TurretHead = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Head"));
	TurretHead->SetupAttachment(RootComponent);
	TurretHead->AddLocalOffset(FVector::ZeroVector);


	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Sphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetGenerateOverlapEvents(true);
	OverlapSphere->AddLocalOffset(FVector::ZeroVector);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->AddLocalOffset(FVector::ZeroVector);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera->AddLocalOffset(FVector::ZeroVector);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(TurretHead);
	Muzzle->AddLocalOffset(FVector::ZeroVector);
}

void ADETurretPawn::BeginPlay() {
	Super::BeginPlay();
	
}

void ADETurretPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADETurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ADETurretPawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ADETurretPawn::LookUp);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADETurretPawn::Fire);
}

void ADETurretPawn::Turn(float Value) {
	AddControllerYawInput(Value);
	TurretHead->SetRelativeRotation(FollowCamera->GetComponentRotation().Quaternion());
}

void ADETurretPawn::LookUp(float Value) {
	AddControllerPitchInput(Value);
	TurretHead->SetRelativeRotation(FollowCamera->GetComponentRotation().Quaternion());
}

void ADETurretPawn::Fire() {
	ServerFire(Muzzle->GetComponentLocation(), TurretHead->GetComponentRotation());
}

bool ADETurretPawn::ServerFire_Validate(FVector Location, FRotator Direction) { return true; }

void ADETurretPawn::ServerFire_Implementation(FVector Location, FRotator Direction) {
	if(!Projectile) return;
	GetWorld()->SpawnActor<AProjectile>(Projectile, Location, Direction);
}

