// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameStateControllerInterface.h"
#include "GameFramework/GameModeBase.h"
#include "TrickyGameModeBase.generated.h"

/**
 * A custom game mode base class that provides extensive functionality
 * to control the game state and gameplay flow. 
 */
UCLASS(Blueprintable, BlueprintType)
class TRICKYGAMEMODE_API ATrickyGameModeBase : public AGameModeBase, public IGameStateControllerInterface
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;

	/**
	 * A delegate that is triggered when the game starts.
	 * This delegate can be bound to dynamically in Blueprint to handle game start events,
	 * allowing external scripts or logic to respond to the beginning of the game.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameStartedDynamicSignature OnGameStarted;

	/**
	 * A dynamic multicast delegate that is triggered when the game finishes, broadcasting the result of the game.
	 * Allows listeners to respond to the conclusion of a game, providing the game's final outcome as a parameter.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameFinishedDynamicSignature OnGameFinished;

	/**
	 * A dynamic delegate that is broadcast when the game is paused.
	 * Enables Blueprint functionality to respond to the game entering the paused state.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGamePausedDynamicSignature OnGamePaused;

	/**
	 * A delegate that is broadcasted when the game is unpaused.
	 * Allows external systems or components to respond when the game state transitions
	 * from paused to its previous state.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameUnpausedDynamicSignature OnGameUnpaused;

	/**
	 * Delegate that is triggered when the game stops, providing a reason for the stoppage.
	 * This event can be used to perform actions or notify systems when the game transitions to an inactive state.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameStoppedDynamicSignature OnGameStopped;

	/**
	 * A delegate that is triggered when the inactivity reason of the game state changes.
	 * It allows external systems to react to updates in the game's inactivity reason,
	 * enabling dynamic responses to changes in the game's flow or state.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameInactivityReasonChangedDynamicSignature OnInactivityReasonChanged;

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameInactivityReason GetInitialInactivityReason() const { return InitialInactivityReason; };

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetInitialInactivityReason(const EGameInactivityReason Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameInactivityReason GetCurrentInactivityReason() const { return CurrentInactivityReason; };

	UFUNCTION(BlueprintCallable, Category=GameState)
	FORCEINLINE EGameState GetCurrentState() const { return CurrentState; };

	UFUNCTION(BlueprintCallable, Category=GameState)
	FORCEINLINE EGameState GetLastState() const { return LastState; };

	virtual bool StartGame_Implementation() override;

	virtual bool FinishGame_Implementation(const EGameResult Result) override;

	virtual bool StopGame_Implementation(const EGameInactivityReason Reason) override;

	virtual bool StartPreparation_Implementation() override;

	virtual bool StartCutscene_Implementation() override;

	virtual bool StartTransition_Implementation() override;

	virtual EGameResult GetGameResult_Implementation() const override;

private:
	UPROPERTY(EditInstanceOnly,
		BlueprintGetter=GetInitialInactivityReason,
		BlueprintSetter=SetInitialInactivityReason,
		Category=GameState)
	EGameInactivityReason InitialInactivityReason = EGameInactivityReason::Transition;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetCurrentInactivityReason, Category=GameState)
	EGameInactivityReason CurrentInactivityReason = EGameInactivityReason::Transition;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetCurrentState, Category=GameState)
	EGameState CurrentState = EGameState::Inactive;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetLastState, Category=GameState)
	EGameState LastState = EGameState::Inactive;

	UPROPERTY(VisibleAnywhere, Category=GameState)
	EGameResult GameResult = EGameResult::None;

	virtual bool PauseGame_Implementation() override;

	virtual bool UnpauseGame_Implementation() override;
	
	virtual bool ChangeInactivityReason_Implementation(const EGameInactivityReason NewInactivityReason) override;

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	void PrintWarning(const FString& Message) const;

	void PrintLog(const FString& Message) const;

	static void GetGameStateName(FString& StateName, const EGameState State);

	static void GetInactivityReasonName(FString& ReasonName, const EGameInactivityReason Reason);

	static void GetGameResultName(FString& ResultName, const EGameResult Result);
#endif
};
