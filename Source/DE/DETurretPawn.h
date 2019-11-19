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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OverlapSphere, meta = (AllowPrivateAccess = "true"))
	USphereComponent* OverlapSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> Projectile;

public:
	// Sets default values for this pawn's properties
	ADETurretPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Turn(float Value);
	void LookUp(float Value);

	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
