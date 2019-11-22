
#include "Projectile.h"
#include "DETarget.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = true;
	InitialLifeSpan = 10;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
	OverlapBox->SetGenerateOverlapEvents(true);
	OverlapBox->AddLocalOffset(FVector::ZeroVector);
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnComponentBeginOverlap);
}

void AProjectile::BeginPlay() {
	Super::BeginPlay();

}

void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime);
}

void AProjectile::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if(!OtherActor) return;

	ADETarget* Target = Cast<ADETarget>(OtherActor);
	if(Target) {
		Target->ApplyDamage(Damage);
	}
}

float AProjectile::GetDamage() {
	return Damage;
}
