// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Player/TowerPlayerState.h"

ATowerPlayerState::ATowerPlayerState()
{
	Health = MaxHealth;
}

void ATowerPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	OnHealthChangeSignature.Broadcast(Health);
}

void ATowerPlayerState::AddHealth(const float InHealthAmount)
{
	Health = FMath::Clamp(Health + InHealthAmount, 0.f, MaxHealth);
	OnHealthChangeSignature.Broadcast(Health);
	
	if (Health <= 0.f)
	{
		OnPlayerDeathSignature.Broadcast();
	}
}

void ATowerPlayerState::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

void ATowerPlayerState::WithdrawGold(const float Amount)
{
	if (Amount < 0 || Amount > Gold) return;
	
	Gold -= Amount;
	OnPlayerGoldChangeSignature.Broadcast(Gold);
}

void ATowerPlayerState::DepositGold(const float Amount)
{
	if (Amount < 0) return;
	
	Gold += Amount;
	OnPlayerGoldChangeSignature.Broadcast(Gold);
}

void ATowerPlayerState::AddPlacedTower(ATowerActorBase* NewTower)
{
	PlacedTowers.Add(NewTower);
}

void ATowerPlayerState::RemoveTower(ATowerActorBase* InTower)
{
	PlacedTowers.Remove(InTower);
}
