
#include "DEPlayerController.h"

void ADEPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &ADEPlayerController::Interact);
}

bool ADEPlayerController::Interact_Validate() { return true; }

void ADEPlayerController::Interact_Implementation() {
	if(!DefaultCharacter) return;

	if(GetPawn()->GetClass() == DefaultCharacter->GetClass()) {
		if(DefaultCharacter) {
			DefaultCharacter->Interact();
		}	
	}
	else {
		Possess(DefaultCharacter);
	}
}

void ADEPlayerController::SetDefaultCharacter(ADECharacter* Character) {
	DefaultCharacter = Character;
}

ADECharacter * ADEPlayerController::GetDefaultCharacter() {
	return DefaultCharacter;
}
