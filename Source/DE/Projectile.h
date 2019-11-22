// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Projectile.generated.h"

UCLASS()
class DE_API AProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OverlapBox, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OverlapBox, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* OverlapBox;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetDamage();
};
