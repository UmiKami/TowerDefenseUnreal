// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TowerPlayerState.generated.h"

class ATowerActorBase;
/**
 * @brief Manages state of the player including health and owned stuff.
 *
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ATowerPlayerState();
	
	/**
	 * 
	 * @return Current Health of the player.
	 */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const {return Health;} 
	
	/**
	 * 
	 * @return Current MaxHealth of the player.
	 */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;} 
	
	
	/**
	 * 
	 * @return List of all towers placed in the world owned by the player.
	 */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<TObjectPtr<ATowerActorBase>> GetOwnedTowers() const {return PlacedTowers;} 
	
	/**
	 * @brief Adds tower just placed in the world to tracker.
	 * 
	 * @param NewTower Tower being placed in the world.
	 */
	UFUNCTION()
	void AddPlacedTower(ATowerActorBase* NewTower);
	
	/**
	 * 
	 * @param InTower Tower that needs to be deleted from tracker.
	 */
	UFUNCTION()
	void RemoveTower(ATowerActorBase* InTower);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.f;
	
	/**
	 * @brief Keeps track of player own towers.
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<ATowerActorBase>> PlacedTowers;
};
