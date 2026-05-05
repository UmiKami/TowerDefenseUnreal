// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class ATowerActorGhostMirror;
enum class ETowerClass : uint8;
class UTowerClassInfo;
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
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsHoldingGhostTower() const { return GhostMesh != nullptr; }
	
	UFUNCTION(BlueprintCallable)
	void AttachMeshToFollowCursor(ETowerClass TowerClass, int32 TowerLevel = 1);
	
	virtual void Tick(float DeltaSeconds) override;
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
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTowerWidgetController> WidgetControllerClass;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> EscapeAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> RightMouseAction;
	
	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UInputAction> LeftMouseAction;
	
	UPROPERTY(EditDefaultsOnly, Category="UI|Gameplay Actions")
	TObjectPtr<UTowerClassInfo> TowerClassInfo;
	
	UPROPERTY()
	TObjectPtr<ATowerActorGhostMirror> GhostMesh;

private:
	void OnEscape(const FInputActionValue& Value);
	void OnRMB(const FInputActionValue& InputActionValue);
	void OnLMB(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void OnGameOver();
};
