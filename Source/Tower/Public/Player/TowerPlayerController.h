// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerPlayerController.generated.h"

class UInputMappingContext

/**
 * @brief Custom player controller for input setup
 * @ingroup Tower
 */
UCLASS()
class TOWER_API ATowerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets mouse cursor visibility to true.
	 */
	ATowerPlayerController();
	
protected:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
};
