// Copyright UmiKami (Ernesto Gonzalez) © 2026

#include "Player/TowerPlayerController.h"
#include "EnhancedInputSubsystems.h"

ATowerPlayerController::ATowerPlayerController()
{
	bShowMouseCursor = true;
}

void ATowerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	checkf(DefaultMappingContext, TEXT("Default input mapping context not set in Tower Player Controller."));
	
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
