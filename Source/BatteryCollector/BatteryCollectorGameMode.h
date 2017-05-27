// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "BatteryCollectorGameMode.generated.h"


// Enum to store the current state of gameplay
//UENUM(BlueprintType)
//enum class EBatteryPlayState{EPlaying,EGameOver,EWon,EUnknown};
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying UMETA(DisplayName = "Playing"),
	EGameOver UMETA(Displayname = "Game Over"),
	EWon UMETA(DisplayName = "Won"),
	EUnknown UMETA(DisplayName = "Unknown")
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();

	virtual void Tick(float DeltaTime) override;

	// Rtn's power needed to win for the HUD
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;

	virtual void BeginPlay() override;

	// Rtn's current playing state
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;

	// Sets a new playing state
	void SetCurrentState(EBatteryPlayState NewState);

protected:
	// The rate at which the character loses power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float DecayRate;

	// Power needed to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float PowerToWin;

	// Widget class to use for our HUD screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	// Actual instance of our HUD
	UPROPERTY()
	class UUserWidget* CurrentWidget;

private:
	// Keeps track of the current playing state
	EBatteryPlayState CurrentState;

	TArray<class ASpawnVolume*> SpawnVolumeActors;

	// Handle any f'n calls that rely upon changing the playing state of our game
	void HandleNewState(EBatteryPlayState NewState);

};



