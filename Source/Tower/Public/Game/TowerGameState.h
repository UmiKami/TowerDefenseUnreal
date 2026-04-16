// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TowerGameState.generated.h"

/**
 * @brief Manages the game state for the Tower game mode.
 *
 * Tracks score, wave number, and player stats.
 * 
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetSpawnRate() const { return EnemySpawnRateCurve.Eval(Wave, "SpawnRateCurve not found."); }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetSpawnLimit() const { return SpawnLimitPerWaveCurve.Eval(Wave, "SpawnRateCurve not found."); }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Match Stats", meta=(DisplayPriority=0))
	int32 Wave = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match Stats", meta=(DisplayPriority=0))
	int32 EnemiesPendingSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Match Stats", meta=(DisplayPriority=0))
	int32 RemainingEnemyCount;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Match Stats", meta=(DisplayPriority=0))
	int32 EnemiesKilled;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match Stats", meta=(DisplayPriority=0))
	FCurveTableRowHandle SpawnLimitPerWaveCurve;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match Stats", meta=(DisplayPriority=0))
	FCurveTableRowHandle EnemySpawnRateCurve;
};
