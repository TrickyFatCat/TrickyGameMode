// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStateControllerInterface.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Inactive,
	Active,
	Finished,
	Paused
};

UENUM(BlueprintType)
enum class EGameResult : uint8
{
	Win,
	Loose,
	Draw
};

UENUM(BlueprintType)
enum class EGameInactivityReason : uint8
{
	Preparation,
	Cutscene,
	Custom
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFinishedDynamicSignature, const EGameResult, Result);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePausedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUnpausedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStoppedDynamicSignature, const EGameInactivityReason, Reason);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UGameStateControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TRICKYGAMEMODE_API IGameStateControllerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool StartGame();

	virtual bool BeginGame_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool FinishGame(const EGameResult Result);

	virtual bool FinishGame_Implementation(const EGameResult Result);

	UFUNCTION(Blueprintable, BuleprintNativeEvent, Category = GameState)
	bool StopGame(const EGameInactivityReason Reason);

	virtual bool StopGame_Implementation(const EGameInactivityReason Reason);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool PauseGame();

	virtual bool PauseGame_Implementation();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool UnpauseGame();

	virtual bool UnpauseGame_Implementation();
};
