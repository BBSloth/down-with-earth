
#include "DETurretActor.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "DEPlayerController.h"

ADETurretActor::ADETurretActor()
{
	PrimaryActorTick.bCanEverTick = true;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap Sphere"));
	OverlapSphere->SetGenerateOverlapEvents(true);
	SetRootComponent(OverlapSphere);

	TurretBase = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Base"));
	SetRootComponent(TurretBase);

	TurretHead = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Head"));
	TurretHead->SetupAttachment(TurretBase);
	TurretHead->AddLocalOffset(FVector::ZeroVector);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(TurretHead);
	Muzzle->AddLocalOffset(FVector::ZeroVector);
}

void ADETurretActor::BeginPlay() {
	Super::BeginPlay();
	
	FireTimer = 0;
}

void ADETurretActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	ServerTick(DeltaTime);
}

void ADETurretActor::ServerTick(float DeltaTime) {
	if(GetNetMode() == NM_Client) return;

	if(FireTimer < FireRate) FireTimer += DeltaTime;
	else AttemptFire();

	if(Target) {
		FVector Direction = Target->GetActorLocation() - GetActorLocation();
		TurretHead->SetWorldRotation(Direction.Rotation());
	}
}

void ADETurretActor::FindTarget() {
	Target = NULL;

	FConstPlayerControllerIterator ControllerIterator = GetWorld()->GetPlayerControllerIterator();

	for(ControllerIterator; ControllerIterator; ControllerIterator++) {
		ADEPlayerController* PlayerController = Cast<ADEPlayerController>(*ControllerIterator);
		if(!PlayerController) continue;

		ADECharacter* Character = PlayerController->GetDefaultCharacter();
		if(!Character) continue;

		FVector Direction = Character->GetActorLocation() - GetActorLocation();
		Direction.Normalize();

		float DotProduct = FVector::DotProduct(Direction, GetActorForwardVector());
		float AngleToDot = 1 - (MaxTargetAngle / 180);
	
		if(DotProduct < AngleToDot) continue;

		Target = Character;
	}
}

void ADETurretActor::AttemptFire() {
	FindTarget();
	if(!Target) return;
	Fire();
}

void ADETurretActor::Fire() {
	if(!Projectile) return;

	FVector Direction = Target->GetActorLocation() - GetActorLocation();
	FVector Location = Muzzle->GetComponentLocation();

	GetWorld()->SpawnActor<AProjectile>(Projectile, Location, Direction.Rotation());

	FireTimer = 0;
}
