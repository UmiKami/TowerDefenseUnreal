// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "Data/TowerClassInfo.h"
#include "GameFramework/Actor.h"
#include "Interaction/TowerHighlightInterface.h"
#include "Containers/SpscQueue.h"
#include "TowerActorBase.generated.h"

class UTowerActorContextMenuWidgetController;
class UWidgetComponent;
class ATowerEnemyPawn;
class UBoxComponent;
enum class ETowerClass : uint8;
class UTowerClassInfo;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTowerLevelChangeSignature, int32, NewTowerLevel);

/**
 * @brief The actual tower actor player will be spawning in the world.
 * 
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerActorBase : public AActor, public ITowerHighlightInterface
{
	GENERATED_BODY()

public:
	ATowerActorBase();
	virtual void Tick(float DeltaSeconds) override;
	
	/**
	 * @brief Sets the tower class that needs to be spawned.
	 * 
	 * @note This must be called on Deferred Spawn as mesh needs to be set before it is spawned and
	 * this is based on the TowerClass.
	 * 
	 * @param InTowerClass Type of tower to be spawn. @see ETowerClass
	 */
	void SetTowerClass(const ETowerClass& InTowerClass); 
	void SetTowerLevel(int32 InLevel); 
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetTowerLevel() const {return Level;}
	
	virtual void ActorSelected() override;
	virtual void ActorDeselected() override;

	/**
	 * 
	 * @return Returns the cost of the tower at level 1. Aka Base Cost.
	 */
	UFUNCTION(BlueprintPure)
	float GetBaseCost() const;
	
	UFUNCTION(BlueprintCallable)
	float GetUpgradeCost() const;
	
	UFUNCTION(BlueprintCallable)
	float GetDowngradeRefund() const;

	UFUNCTION(BlueprintCallable)
	void UpgradeTower();
	
	UFUNCTION(BlueprintCallable)
	void DowngradeTower();

protected:
	virtual void BeginPlay() override;
	void Fire();

	/**
	 * @brief This function is used to detect when enemies are within range of tower and launch projectiles accordingly.
	 */
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	/**
	 * @brief This function removes target that is still alive
	 */
	UFUNCTION()
	void OnActorOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void SetCollisionEnable(bool bEnabled) const;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxCollider;
	/**
	 * @brief Cosmetic mesh that is mostly invisible and allows to check for collision overlaps within @see TowerAttackRange.
	 * 
	 * @note This mesh is a cylinder mesh with the radius being the same as TowerAttackRange
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> TowerRangeDiskMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> TowerMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> TowerContextMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UTowerActorContextMenuWidgetController> ContextMenuWidgetControllerClass;
	
	/**
	 * @brief Determines how far the tower can shoot from and detect enemies.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TowerAttackRange = 20.f;
	
	/**
	 * @brief Tower level is used to determine damage and display mesh among other things.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "4", UIMin = "1", UIMax = "4"))
	int32 Level = 1;
	
	/**
	 * @brief Amount of damage tower projectile will deal. Based on a curve.
	 */ 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 10.f;
	
	/**
	 * @brief How often the tower will fire. Based on a curve. Lower Value = Faster/Better
	 */ 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireRate = 1.f;
	
	/**
	 * @brief Type of tower. E.g. Cannon, Archer, Wizard, Poison
	 * 
	 * @see ETowerClass
	 */
	UPROPERTY(EditDefaultsOnly)
	ETowerClass TowerClass = ETowerClass::Archer;
	
	/**
	 * @brief Data asset that contains information needed by this actor to spawn with correct mesh and stats.
	 * 
	 * @see UTowerClassInfo
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTowerClassInfo> TowerClassInfo;
	
	UPROPERTY()
	TArray<TObjectPtr<ATowerEnemyPawn>> Targets;
	
	UPROPERTY(BlueprintAssignable)
	FOnTowerLevelChangeSignature OnTowerLevelChange;

private:
	UFUNCTION()
	void OnTargetDeath(ATowerEnemyPawn* EnemyPawn);
	
	UFUNCTION()
	void DisplayContextMenu();
	
	UFUNCTION()
	void HideContextMenu();
	
	void UpdateTowerLevelBasedProperties();
	
	FTowerClasDefaultInfo* TowerClasDefaultInfo;
	
	FTimerHandle FireRateTimer;
};
