// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TowerPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangeSignature, float, NewGoldAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathSignature);

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
	 * @return Current amount of gold that can be spent by the player.
	 */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetGoldAmount() const { return Gold;}
	
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
	* @brief Adds to current player health
	*/
	UFUNCTION()
	void AddHealth(const float InHealthAmount); 
	
	/**
	* @brief Sets a new value for MaxHealth 
	*/
	UFUNCTION()
	void SetMaxHealth(const float NewMaxHealth); 
	
	UFUNCTION(BlueprintCallable)
	void WithdrawGold(const float Amount); 
	
	UFUNCTION(BlueprintCallable)
	void DepositGold(const float Amount);
	
	/**
	 * 
	 * @return List of all towers placed in the world owned by the player.
	 */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE TArray<ATowerActorBase*> GetOwnedTowers() const {return PlacedTowers;} 
	
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
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChangeSignature;
	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerDeathSignature OnPlayerDeathSignature;
	
	UPROPERTY(BlueprintAssignable)
	FOnGoldChangeSignature OnPlayerGoldChangeSignature;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	float Gold = 100.f;	
	
	/**
	 * @brief Keeps track of player own towers.
	 */
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<ATowerActorBase>> PlacedTowers;
};
