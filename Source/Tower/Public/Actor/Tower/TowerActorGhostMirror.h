// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerActorGhostMirror.generated.h"

class ATowerSnapArea;
enum class ETowerClass : uint8;

UCLASS()
class TOWER_API ATowerActorGhostMirror : public AActor
{
	GENERATED_BODY()

public:
	ATowerActorGhostMirror();

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly)
	ETowerClass TowerClass;
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "1", ClampMax = "4", UIMin = "1", UIMax = "4"))
	int32 Level = 1;
	
	UPROPERTY(VisibleAnywhere)
	bool bSnappedToArea = false;
	
	UPROPERTY()
	TObjectPtr<ATowerSnapArea> CurrentSnapArea = nullptr;
};
