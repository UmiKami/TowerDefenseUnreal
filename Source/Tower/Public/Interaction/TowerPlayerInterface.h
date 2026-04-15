// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TowerPlayerInterface.generated.h"


class ATowerPlayerCharacter;
// This class does not need to be modified.
UINTERFACE()
class UTowerPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWER_API ITowerPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual AActor* GetActorRef() = 0;
};
