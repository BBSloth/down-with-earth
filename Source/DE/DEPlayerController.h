// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DECharacter.h"
#include "DEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DE_API ADEPlayerController : public APlayerController
{
	GENERATED_BODY()

	ADECharacter* DefaultCharacter;

	UFUNCTION(Server, Reliable, WithValidation)
	void Interact();

protected:
	virtual void SetupInputComponent() override; 

public:
	void SetDefaultCharacter(ADECharacter* Character);
	ADECharacter* GetDefaultCharacter();
	
};
