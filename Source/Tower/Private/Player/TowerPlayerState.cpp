// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Player/TowerPlayerState.h"

ATowerPlayerState::ATowerPlayerState()
{
	Health = MaxHealth;
}

void ATowerPlayerState::AddPlacedTower(ATowerActorBase* NewTower)
{
	PlacedTowers.Add(NewTower);
}

void ATowerPlayerState::RemoveTower(ATowerActorBase* InTower)
{
	PlacedTowers.Remove(InTower);
}
