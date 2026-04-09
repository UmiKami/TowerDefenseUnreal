// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TowerHighlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTowerHighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @ingroup Tower
 */
class TOWER_API ITowerHighlightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ActorSelected() = 0;
	
	virtual void ActorDeselected() = 0;
};
