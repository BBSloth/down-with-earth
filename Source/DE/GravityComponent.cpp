// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityComponent.h"
#include "Kismet/GameplayStatics.h"

UGravityComponent::UGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = UGameplayStatics::GetActorOfClass(this, AGravitySource::StaticClass());

	if(Actor) { 
		GravitySource = Cast<AGravitySource>(Actor);
	}

	UActorComponent* ActorComponent = GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass());
	if(ActorComponent) {
		MovementComponent = Cast<UCharacterMovementComponent>(ActorComponent);
	}
}


void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!GravitySource) return;

	AActor* Actor = GetOwner();

	FVector GravityDirection = Actor->GetActorLocation() - GravitySource->GetActorLocation();

	if(MovementComponent) {
		FRotator CharacterRotation = Actor->GetActorRotation();
		FRotator GravityRotation = GravityDirection.Rotation().Add(90, 0, 0);
		FRotator NewCharacterRotation = FRotator(GravityRotation.Pitch, GravityRotation.Yaw, GravityRotation.Roll);

		Actor->SetActorRotation(NewCharacterRotation.Quaternion());
		MovementComponent->AddForce(GravityDirection * GravitySource->GetGravityScale());
		if(MovementComponent->IsMovingOnGround())
		UE_LOG(LogTemp, Warning, TEXT("MOVE"))
	}
}

