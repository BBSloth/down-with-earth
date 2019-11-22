// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "Projectile.h"
#include "DETurretPawn.generated.h"

UCLASS()
class DE_API ADETurretPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TurretBase, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TurretHead, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretHead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TurretHead, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = OverlapSphere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> Projectile;

public:
	ADETurretPawn();

protected:
	virtual void BeginPlay() override;

	void Turn(float Value);
	void LookUp(float Value);

	void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire(FVector Location, FRotator Direction);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
