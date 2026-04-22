// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/TowerPlayerInterface.h"
#include "TowerPlayerStronghold.generated.h"

class UBoxComponent;
class ATowerGameState;
class ATowerPlayerState;
/**
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerPlayerStronghold : public AActor, public ITowerPlayerInterface
{
	GENERATED_BODY()

public:
	ATowerPlayerStronghold();

	virtual AActor* GetActorRef() override;
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void Die();
	
	/**
	 * @brief This function is called after health has been deducted to play any sort of cues to indicate stronghold has been hit
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void PostTakeDamageAction();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StrongholdMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxCollision;
private:
	
	UPROPERTY(VisibleAnywhere, Category="Data Points", meta=(DisplayPriority=0))
	TObjectPtr<ATowerPlayerState> TowerPlayerState;
	
	UPROPERTY(VisibleAnywhere, Category="Data Points", meta=(DisplayPriority=0))
	TObjectPtr<ATowerGameState> TowerGameState;
	
};
