
#include "DEPlayerController.h"

void ADEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("SETUP"));

	InputComponent->BindAction("Interact", IE_Pressed, this, &ADEPlayerController::Interact);
}

void ADEPlayerController::SetDefaultCharacter(ADECharacter* Character)
{
	DefaultCharacter = Character;
}

void ADEPlayerController::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerCotnr"));

	if(GetPawn()->GetClass() == DefaultCharacter->GetClass()) {
		if(DefaultCharacter) {
			DefaultCharacter->Interact();
		}	
	}
	else {
		Possess(DefaultCharacter);
	}
}
