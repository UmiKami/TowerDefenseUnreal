// Copyright UmiKami (Ernesto Gonzalez) © 2026


#include "Game/TowerGameMode.h"

#include "Game/TowerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TowerPlayerState.h"

void ATowerGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if(!TowerGameState) TowerGameState = GetGameState<ATowerGameState>();
	checkf(TowerGameState, TEXT("Invalid Tower Game State"));
	
	if (TowerGameState->State == Playing)
	{
		StartNextWave();
	}
	
	if ( ATowerPlayerState* Player = Cast<ATowerPlayerState>( UGameplayStatics::GetPlayerState(this, 0)) )
	{
		Player->OnPlayerDeathSignature.AddDynamic(this, &ThisClass::SetGameOver);
	}
}

void ATowerGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (!TowerGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("INVALID: Tower Game State"))
		return;
	}
	
	if (TowerGameState->State != Playing)
	{
		UE_LOG(LogTemp, Warning, TEXT("CAUTION: Not in playing state."))
		return;
	}
	
	
	if (TowerGameState->RemainingEnemyCount == 0 && TowerGameState->EnemiesPendingSpawn == 0)
	{
		TowerGameState->State = Playing_WaveTransition;
		StartNextWave();
	}
	
	TowerGameState->IncreaseGameTimer(DeltaSeconds);
}

void ATowerGameMode::ChangeGameState(const ETowerGameState NewGameState) const
{
	TowerGameState->State = NewGameState;
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
	
	TowerGameState->State = Playing;
}

void ATowerGameMode::StopSpawningEnemy()
{
	GetWorldTimerManager().ClearTimer(EnemySpawnTimer);
}

void ATowerGameMode::SetGameOver()
{
	TowerGameState->State = GameOver;
	
	OnGameOverSignature.Broadcast();
	
	UGameplayStatics::SetGamePaused(this, true);
}

