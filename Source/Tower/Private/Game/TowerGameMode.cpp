// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Game/TowerGameMode.h"

#include "Game/TowerGameState.h"

void ATowerGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if(!TowerGameState) TowerGameState = GetGameState<ATowerGameState>();
	checkf(TowerGameState, TEXT("Invalid Tower Game State"));
	
	StartNextWave();
}

void ATowerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!TowerGameState) return;
	
	if (TowerGameState->RemainingEnemyCount == 0)
	{
		StartNextWave();
	}
}

void ATowerGameMode::StartNextWave()
{
	StopSpawningEnemy();
	
	
	TowerGameState->Wave++;
	TowerGameState->RemainingEnemyCount = TowerGameState->GetSpawnLimit();
	TowerGameState->EnemiesPendingSpawn = TowerGameState->GetSpawnLimit();
	
	UE_LOG(LogTemp, Warning, TEXT("Current Wave: %d"), TowerGameState->Wave);
	UE_LOG(LogTemp, Warning, TEXT("Enemy Spawn Limit: %d"), TowerGameState->EnemiesPendingSpawn);

	DelayBeforeNextWave = 0;
	GetWorldTimerManager().SetTimer(EnemySpawnTimer, this, &ThisClass::SpawnEnemy, TowerGameState->GetSpawnRate(), true, DelayBeforeNextWave);
}

void ATowerGameMode::StopSpawningEnemy()
{
	GetWorldTimerManager().ClearTimer(EnemySpawnTimer);
}

