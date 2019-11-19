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

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Base"));
	TurretBase->SetupAttachment(RootComponent);
	TurretBase->AddLocalOffset(FVector(0, 0, 0));

	TurretHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Head"));
	TurretHead->SetupAttachment(TurretBase);
	TurretHead->AddLocalOffset(FVector(0, 0, 0));

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Sphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetGenerateOverlapEvents(true);
	OverlapSphere->AddLocalOffset(FVector(0, 0, 0));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(TurretHead);
	Muzzle->AddLocalOffset(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void ADETurretPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADETurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADETurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn", this, &ADETurretPawn::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ADETurretPawn::LookUp);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADETurretPawn::Fire);
}

void ADETurretPawn::Turn(float Value)
{
	AddControllerYawInput(Value);
	FRotator TurretBaseRotation = FRotator(0, FollowCamera->GetComponentRotation().Yaw, 0);
	TurretBase->SetRelativeRotation(TurretBaseRotation.Quaternion());
}

void ADETurretPawn::LookUp(float Value)
{
	AddControllerPitchInput(Value);
	FRotator TurretHeadRotation = FRotator(FollowCamera->GetComponentRotation().Pitch, 0, 0);
	TurretHead->SetRelativeRotation(TurretHeadRotation.Quaternion());
}

void ADETurretPawn::Fire()
{
		UE_LOG(LogTemp, Warning, TEXT("FIRE"));

	if(!Projectile) return;
		UE_LOG(LogTemp, Warning, TEXT("PRoj"));

	FVector Location = Muzzle->GetComponentLocation();
	FRotator Rotation = TurretHead->GetComponentRotation();
	GetWorld()->SpawnActor<AProjectile>(Projectile, Location, Rotation);
}

