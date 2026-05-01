// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TowerSnapArea.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class TOWER_API ATowerSnapArea : public AActor
{
	GENERATED_BODY()
	
public:
	ATowerSnapArea();
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SnapAreaRecognitionRangeMesh;
};
