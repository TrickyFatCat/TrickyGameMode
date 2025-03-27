// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TrickyGameModeLibrary.generated.h"

enum class ETrickyGameState : uint8;
enum class EGameResult : uint8;
enum class EGameInactivityReason : uint8;
class ATrickyGameModeBase;

/**
 * Provides utility functions related to the Tricky GameMode.
 */
UCLASS()
class TRICKYGAMEMODE_API UTrickyGameModeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Retrieves the current game mode cast to the TrickyGameMode type.
	 *
	 * @return A pointer to the TrickyGameMode.
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static ATrickyGameModeBase* GetTrickyGameMode(const UObject* WorldContextObject);

	/**
	 * Initiates the start of the game, transitioning it into an active state.
	 *
	 * @return True if the game was successfully started.
	 */
	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartGame(const UObject* WorldContextObject);

	/**
	 * Stops the ongoing game and transitions it out of an active state based on the specified inactivity reason.
	 *
	 * @param Reason The reason for the game's inactivity.
	 * @return True if the game was successfully stopped.
	 */
	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StopGame(const UObject* WorldContextObject, EGameInactivityReason Reason);

	/**
	 * Completes the game based on the provided result.
	 *
	 * @param Result The result of the game.
	 * @return True if the game was successfully finished.
	 */
	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool FinishGame(const UObject* WorldContextObject, EGameResult Result);

	/**
	 * Updates the current inactivity reason for the game.
	 *
	 * @param Reason The new inactivity reason.
	 * @return True if the inactivity reason was successfully changed.
	 */
	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool ChangeInactivityReason(const UObject* WorldContextObject, EGameInactivityReason Reason);

	/**
	 * Initiates the preparation phase of the game.
	 *
	 * @return True if the preparation phase was successfully started.
	 */
	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartPreparation(const UObject* WorldContextObject);

	/**
	 * Initiates the start of a cutscene within the game.
	 *
	 * @return True if the cutscene was successfully started.
	 */
	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartCutscene(const UObject* WorldContextObject);

	/**
	 * Initiates the transitioning phase within the game.
	 *
	 * @return True if the transition process was successfully started.
	 */
	UFUNCTION(BlueprintCallable, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static bool StartTransition(const UObject* WorldContextObject);

	/**
	 * Returns the current state of the game.
	 * 
	 * @return The current game state.
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static ETrickyGameState GetGameState(const UObject* WorldContextObject);

	/**
	 * Returns the current result of the game.
	 *
	 * @return The current game result.
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static EGameResult GetGameResult(const UObject* WorldContextObject);

	/**
	 * Returns the current inactivity reason.
	 * 
	 * @return The current inactivity reason
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static EGameInactivityReason GetInactivityReason(const UObject* WorldContextObject);

	/**
	 * Retrieves the elapsed time since the game started.
	 *
	 * @return elapsed game time in seconds.
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGameElapsedTime(const UObject* WorldContextObject);

	/**
	 * Retrieves the remaining time for the ongoing game.
	 *
	 * @return remaining game time in seconds.
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGameRemainingTime(const UObject* WorldContextObject);

	/**
	 * Retrieves the remaining time of preparation timer.
	 *
	 * @return remaining preparation time in seconds.
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGamePreparationRemainingTime(const UObject* WorldContextObject);

	/**
	 * Retrieves the elapsed time of preparation timer.
	 *
	 * @return elapsed preparation time in seconds.
	 */
	UFUNCTION(BlueprintPure, Category=TrickyGameMode, meta=(WorldContext="WorldContextObject"))
	static float GetGamePreparationElapsedTime(const UObject* WorldContextObject);

private:
	UFUNCTION()
	static bool ImplementsGameStateInterface(const UObject* WorldContextObject);
};
