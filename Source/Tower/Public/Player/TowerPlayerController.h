// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerPlayerController.generated.h"

class UTowerWidgetController;
class UTowerUserWidget;
class UInputMappingContext;

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
	
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY()
	TObjectPtr<UTowerUserWidget> PlayerHUD;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDClass; 
	
	UPROPERTY()
	TObjectPtr<UTowerUserWidget> GameOverWidget;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Tower|UI")
	TSubclassOf<UTowerWidgetController> WidgetControllerClass;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
private:
	
	UFUNCTION()
	void DisplayGameOverOverlay();
};
