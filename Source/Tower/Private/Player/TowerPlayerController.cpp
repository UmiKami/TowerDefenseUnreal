// Copyright UmiKami (Ernesto Gonzalez) © 2026

#include "Player/TowerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Player/TowerPlayerState.h"
#include "Game/TowerGameMode.h"
#include "Game/TowerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/TowerUserWidget.h"
#include "UserInterface/WidgetController/TowerWidgetController.h"

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

void ATowerPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UUserWidget* PlayerHUDUserWidget = CreateWidget(this, PlayerHUDClass);
	UTowerUserWidget* PlayerHUD= Cast<UTowerUserWidget>(PlayerHUDUserWidget);

	UTowerWidgetController* PlayerHUDWidgetController = NewObject<UTowerWidgetController>(this, WidgetControllerClass);

	const FWidgetControllerParams Params{
		this,
		GetPlayerState<ATowerPlayerState>(),
		Cast<ATowerGameState>(UGameplayStatics::GetGameState(this)),
		Cast<ATowerGameMode>(UGameplayStatics::GetGameMode(this))
	};

	PlayerHUDWidgetController->SetWidgetControllerParams(Params);

	PlayerHUD->AddToViewport();
	
	PlayerHUD->SetWidgetController(PlayerHUDWidgetController);
}
