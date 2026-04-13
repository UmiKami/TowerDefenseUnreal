// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerEnemyPathActor.generated.h"

class USplineComponent;

/**
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerEnemyPathActor : public AActor
{
	GENERATED_BODY()

public:
	ATowerEnemyPathActor();
	
	FORCEINLINE USplineComponent* GetSplinePath() const {return SplinePath;}
protected:
	
	/** @brief Path that enemy pawns will follow during the match */
	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> SplinePath;
};
