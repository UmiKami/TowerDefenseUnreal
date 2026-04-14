// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TowerEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTowerEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @ingroup Tower
 * @brief Base interface for ATowerEnemyPawn enemies.
 * @par Type
 *   Interface
 */
class TOWER_API ITowerEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetCurrentLocation() const;
	
	virtual bool IsValidPtr() const;
};
