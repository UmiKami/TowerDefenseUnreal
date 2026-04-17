// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Game/TowerGameState.h"

#include "GameFramework/GameMode.h"

void ATowerGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (State != Playing) return;
	
	GameTime+=DeltaSeconds;
}
