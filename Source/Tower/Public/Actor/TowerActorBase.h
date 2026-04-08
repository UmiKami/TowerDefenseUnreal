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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TowerAttackRange = 300.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 10.f;
	
	UPROPERTY(EditDefaultsOnly)
	ETowerClass TowerClass = ETowerClass::Archer;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTowerClassInfo> TowerClassInfo;
	
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
