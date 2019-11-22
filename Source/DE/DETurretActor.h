// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "DETurretActor.generated.h"

UCLASS()
class DE_API ADETurretActor : public AActor
{
	GENERATED_BODY()

	float FireTimer;

	AActor* Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	float MaxTargetAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = OverlapSphere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* OverlapSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Turret, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Turret, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Turret, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> Projectile;

	void ServerTick(float DeltaTime);

	void FindTarget();
	void AttemptFire();

	void Fire();
	
public:	
	ADETurretActor();

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
