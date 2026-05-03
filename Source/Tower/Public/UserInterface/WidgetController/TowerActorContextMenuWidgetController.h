// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "TowerWidgetController.h"
#include "TowerActorContextMenuWidgetController.generated.h"

class ATowerActorBase;
/**
 * 
 */
UCLASS()
class TOWER_API UTowerActorContextMenuWidgetController : public UTowerWidgetController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATowerActorBase> OwningTowerActor;
};
