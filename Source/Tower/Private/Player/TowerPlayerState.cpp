// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Player/TowerPlayerState.h"

ATowerPlayerState::ATowerPlayerState()
{
	Health = MaxHealth;
}

void ATowerPlayerState::AddHealth(const float InHealthAmount)
{
	Health = FMath::Clamp(Health + InHealthAmount, 0.f, MaxHealth);
}

void ATowerPlayerState::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

void ATowerPlayerState::AddPlacedTower(ATowerActorBase* NewTower)
{
	PlacedTowers.Add(NewTower);
}

void ATowerPlayerState::RemoveTower(ATowerActorBase* InTower)
{
	PlacedTowers.Remove(InTower);
}
