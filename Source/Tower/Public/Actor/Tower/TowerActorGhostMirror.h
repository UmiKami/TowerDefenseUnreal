// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerActorGhostMirror.generated.h"

UCLASS()
class TOWER_API ATowerActorGhostMirror : public AActor
{
	GENERATED_BODY()

public:
	ATowerActorGhostMirror();

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere)
	bool bSnappedToArea = false;
};
