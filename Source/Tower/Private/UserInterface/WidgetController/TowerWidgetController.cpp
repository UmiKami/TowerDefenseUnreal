// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "UserInterface/WidgetController/TowerWidgetController.h"

void UTowerWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	GameState = Params.GameState;
	GameMode = Params.GameMode;
}
