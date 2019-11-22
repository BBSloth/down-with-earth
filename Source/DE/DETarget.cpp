// Fill out your copyright notice in the Description page of Project Settings.


#include "DETarget.h"
#include "Projectile.h"

// Sets default values
ADETarget::ADETarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADETarget::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
}

// Called every frame
void ADETarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADETarget::ApplyDamage(float Damage) {
	UE_LOG(LogTemp, Warning, TEXT("damage"));
	Health -= Damage;

	if(Health <= 0) {
		Destroy();
	}
}

