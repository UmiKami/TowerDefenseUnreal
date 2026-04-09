// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "Data/TowerClassInfo.h"
#include "GameFramework/Actor.h"
#include "Interaction/TowerEnemyInterface.h"
#include "TowerActorBase.generated.h"


enum class ETowerClass : uint8;
class UTowerClassInfo;


UCLASS()
class TOWER_API ATowerActorBase : public AActor, public ITowerEnemyInterface
{
	GENERATED_BODY()

public:
	ATowerActorBase();
	
	/**
	 * @brief Sets the tower class that needs to be spawned.
	 * 
	 * @note This must be called on Deferred Spawn as mesh needs to be set before it is spawned and
	 * this is based on the TowerClass.
	 * 
	 * @param InTowerClass Type of tower to be spawn. @see ETowerClass
	 */
	void SetTowerClass(const ETowerClass& InTowerClass); 

protected:
	virtual void BeginPlay() override;

	/**
	 * @brief Cosmetic mesh that is mostly invisible and allows to check for collision overlaps within @see TowerAttackRange.
	 * 
	 * @note This mesh is a cylinder mesh with the radius being the same as TowerAttackRange
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> TowerRangeDiskMesh;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> TowerMesh;
	
	/**
	 * @brief Determines how far the tower can shoot from and detect enemies.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TowerAttackRange = 1.2f;
	
	/**
	 * @brief Tower level is used to determine damage and display mesh among other things.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level = 1;
	
	/**
	 * @brief Amount of damage tower projectile will deal. Based on a curve.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 10.f;
	
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
	
	/**
	 * @brief This function is used to detect when enemies are within range of tower and launch projectiles accordingly.
	 */
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	FTowerClasDefaultInfo* TowerClasDefaultInfo;
};
