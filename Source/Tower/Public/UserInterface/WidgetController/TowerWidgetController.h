// Copyright UmiKami (Ernesto Gonzalez) © 2026

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TowerWidgetController.generated.h"

class ATowerGameMode;
class ATowerGameState;
class ATowerPlayerState;
class ATowerPlayerController;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams()
	{
	}

	FWidgetControllerParams(ATowerPlayerController* PC, ATowerPlayerState* PS, ATowerGameState* GS, ATowerGameMode* GM)
		: PlayerController(PC), PlayerState(PS), GameState(GS), GameMode(GM)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATowerPlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATowerPlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATowerGameState> GameState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ATowerGameMode> GameMode = nullptr;
};

/**
 * @brief Allows user widget access different kind of data
 *
 * @ingroup Tower
 */
UCLASS(Blueprintable)
class TOWER_API UTowerWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& Params);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATowerPlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATowerPlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATowerGameState> GameState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ATowerGameMode> GameMode;
};
