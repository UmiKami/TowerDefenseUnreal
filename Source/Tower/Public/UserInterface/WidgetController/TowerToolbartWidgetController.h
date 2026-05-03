// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "TowerWidgetController.h"
#include "TowerToolbartWidgetController.generated.h"

class UTowerClassInfo;
/**
 * 
 */
UCLASS()
class TOWER_API UTowerToolbartWidgetController : public UTowerWidgetController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTowerClassInfo> TowerClassInfoDataAsset;
};
