// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Actor/TowerProjectileBase.h"
#include "TowerClassInfo.generated.h"
class ATowerActorBase;
class ATowerActorGhostMirror;
/**
 * @brief These are the types of towers that can be spawned.
 * @ingroup Tower
 */
UENUM(BlueprintType)
enum class ETowerClass :uint8
{
	/** Shoots arrows at slow speed. */
	Archer,
	
	/** Shoots arrows at high speed. Increased damage. */
	Ballista,
	
	/** Shoots canon balls. Increased area damage. */
	Cannon,
	
	/** Shoots spells. Highly increased damage, slower fire rate. */
	Wizard,
	
	/** Shoots poison shells. Damage over time, large area of attack. */
	Poison
};

/**
 *	@brief This struct contains information about each class including the amount of damage per level,
 *	and the Mesh that should be displayed at each level 1-4
 *
 * @ingroup Tower
 */
USTRUCT(BlueprintType)
struct FTowerClasDefaultInfo
{
	GENERATED_BODY()
	
	/** @brief Specifies a different mesh per tower level. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Class Defaults")
	TMap<int32,TObjectPtr<USkeletalMesh>> SkeletalMeshComponentPerLevel;
	
	/** @brief Contains amount of damage per level. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Class Defaults")
	FCurveTableRowHandle DamageCurve;
	
	/** @brief Contains fire rate per level. */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Class Defaults")
	FCurveTableRowHandle FireRateCurve;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Class Defaults")
	FCurveTableRowHandle CostPerLevel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Class Defaults", meta = (DisplayName=ProjectileType))
	TSubclassOf<ATowerProjectileBase> ProjectileClass;
};

/**
 * @brief Data asset that contains information about each tower class per level.
 *
 * @ingroup Tower
 */
UCLASS()
class TOWER_API UTowerClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Class Defaults")
	TMap<ETowerClass, FTowerClasDefaultInfo> TowerClassInformation;
	
	/**
	 * @brief This is the material used to display the tower before it is placed, while the user is dragging it with the mouse cursor.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Materials")
	TObjectPtr<UMaterialInstance> GhostMaterialInstance; 
	
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TSubclassOf<ATowerActorGhostMirror> GhostActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TSubclassOf<ATowerActorBase> TowerActorBaseClass;
};
