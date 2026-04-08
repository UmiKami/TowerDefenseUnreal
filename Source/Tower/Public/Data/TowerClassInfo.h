// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TowerClassInfo.generated.h"

UENUM(BlueprintType)
enum class ETowerClass :uint8
{
	Archer,
	Ballista,
	Cannon,
	Wizard,
	Poison
};

USTRUCT(BlueprintType)
struct FTowerClasDefaultInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TMap<int32,TObjectPtr<USkeletalMesh>> SkeletalMeshComponentPerLevel;
	
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TObjectPtr<FRealCurve> DamageCurve;
};

/**
 * 
 */
UCLASS()
class TOWER_API UTowerClassInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TMap<ETowerClass, FTowerClasDefaultInfo> TowerClassInformation;
};
