// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TowerGameMode.generated.h"

class ATowerGameState;
/**
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnEnemy();
	
	UFUNCTION(BlueprintCallable)
	void StartNextWave();
	
	FTimerHandle EnemySpawnTimer;
	
	// TODO Consider evaluating this on a curve so there is less delays between waves the higher up we are
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int DelayBeforeNextWave = 5.f;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ATowerGameState> TowerGameState;
	
private:
	UFUNCTION(BlueprintCallable)
	void StopSpawningEnemy(); 
};
