// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStateControllerInterface.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTrickyGameMode, Log, All)

/**
 * Represents the various states of the game during its lifecycle.
 */
UENUM(BlueprintType)
enum class ETrickyGameState : uint8
{
	Inactive,
	Active,
	Finished
};

/**
 * Represents the possible outcomes of a game session.
 */
UENUM(BlueprintType)
enum class EGameResult : uint8
{
	None,
	Win,
	Loose,
	Draw,
	Custom
};

/**
 * Represents the possible reasons for game inactivity.
 */
UENUM(BlueprintType)
enum class EGameInactivityReason : uint8
{
	None,
	Paused,
	Preparation,
	Cutscene,
	Transition,
	Custom
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedDynamicSignature, const ETrickyGameState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartedDynamicSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFinishedDynamicSignature, const EGameResult, Result);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStoppedDynamicSignature, const EGameInactivityReason, Reason);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameInactivityReasonChangedDynamicSignature,
                                            const EGameInactivityReason, InactivityReason);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UGameStateControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for controlling the game state.
 */
class TRICKYGAMEMODE_API IGameStateControllerInterface
{
	GENERATED_BODY()

public:
	/**
	 * Initiates the start of the game, transitioning it into an active state.
	 *
	 * @return True if the game was successfully started.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool StartGame();

	virtual bool StartGame_Implementation();

	/**
	 * Completes the game based on the provided result.
	 *
	 * @param Result The result of the game.
	 * @return True if the game was successfully finished.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool FinishGame(const EGameResult Result);

	virtual bool FinishGame_Implementation(const EGameResult Result);

	/**
	 * Stops the ongoing game and transitions it out of an active state based on the specified inactivity reason.
	 *
	 * @param Reason The reason for the game's inactivity.
	 * @return True if the game was successfully stopped.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool StopGame(const EGameInactivityReason Reason);

	virtual bool StopGame_Implementation(const EGameInactivityReason Reason);

	/**
	 * Updates the current inactivity reason for the game.
	 *
	 * @param NewInactivityReason The new inactivity reason.
	 * @return True if the inactivity reason was successfully changed.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool ChangeInactivityReason(const EGameInactivityReason NewInactivityReason);

	virtual bool ChangeInactivityReason_Implementation(const EGameInactivityReason NewInactivityReason);

	/**
	 * Initiates the preparation phase of the game.
	 *
	 * @return True if the preparation phase was successfully started.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool StartPreparation();

	virtual bool StartPreparation_Implementation();

	/**
	 * Initiates the start of a cutscene within the game.
	 *
	 * @return True if the cutscene was successfully started.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	bool StartCutscene();

	virtual bool StartCutscene_Implementation();

	/**
	 * Initiates the transitioning phase within the game.
	 *
	 * @return True if the transition process was successfully started.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=GameState)
	bool StartTransition();

	virtual bool StartTransition_Implementation();

	/**
	 * Returns the current state of the game.
	 * 
	 * @return The current game state.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	ETrickyGameState GetGameState() const;

	virtual ETrickyGameState GetGameState_Implementation() const;

	/**
	 * Returns the current result of the game.
	 *
	 * @return The current game result.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	EGameResult GetGameResult() const;

	virtual EGameResult GetGameResult_Implementation() const;

	/**
	 * Returns the current inactivity reason.
	 * 
	 * @return The current inactivity reason
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	EGameInactivityReason GetGameInactivityReason() const;

	virtual EGameInactivityReason GetGameInactivityReason_Implementation() const;

	/**
	 * Retrieves the elapsed time since the game started.
	 *
	 * @return elapsed game time in seconds.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	float GetGameElapsedTime() const;

	virtual float GetGameElapsedTime_Implementation() const;

	/**
	 * Retrieves the remaining time for the ongoing game.
	 *
	 * @return remaining game time in seconds.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = GameState)
	float GetGameRemainingTime() const;

	virtual float GetGameRemainingTime_Implementation() const;
};
