﻿// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

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
	 * Triggered when the game successfully started.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameStartedDynamicSignature OnGameStarted;

	/**
	 * Triggered when the game successfully finished.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameFinishedDynamicSignature OnGameFinished;

	/**
	 * Triggered when the game successfully paused.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGamePausedDynamicSignature OnGamePaused;

	/**
	 * Triggered when the game successfully unpaused.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameUnpausedDynamicSignature OnGameUnpaused;

	/**
	 * Triggered when the game successfully stopped.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameStoppedDynamicSignature OnGameStopped;

	/**
	 * Triggered when the current inactivity reason was successfully changed.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameInactivityReasonChangedDynamicSignature OnInactivityReasonChanged;

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE float GetPreparationDuration() const { return PreparationDuration; }

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetPreparationDuration(const float Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE FTimerHandle GetPreparationTimerHandle() const { return PreparationTimerHandle; }
	
	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameInactivityReason GetInitialInactivityReason() const { return InitialInactivityReason; }

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetInitialInactivityReason(const EGameInactivityReason Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameInactivityReason GetCurrentInactivityReason() const { return CurrentInactivityReason; }

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
	/**
	 * An inactivity reason which will be used when the game mode initialized
	 */
	UPROPERTY(EditInstanceOnly,
		BlueprintGetter=GetInitialInactivityReason,
		BlueprintSetter=SetInitialInactivityReason,
		Category=GameState)
	EGameInactivityReason InitialInactivityReason = EGameInactivityReason::Transition;

	UPROPERTY(EditInstanceOnly,
		BlueprintGetter=GetPreparationDuration,
		BlueprintSetter=SetPreparationDuration,
		Category=GameState,
		meta=(ClampMin="0.0", UIMin="0.0"))
	float PreparationDuration = 3.0f;

	UPROPERTY(BlueprintGetter=GetPreparationTimerHandle, Category=GameState)
	FTimerHandle PreparationTimerHandle;

	/**
	 * Current inacvity reason.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentInactivityReason, Category=GameState)
	EGameInactivityReason CurrentInactivityReason = EGameInactivityReason::Transition;

	/**
	 * Current Game State.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentState, Category=GameState)
	EGameState CurrentState = EGameState::Inactive;

	/**
	 * Last Game State. Used for unpausing the game.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetLastState, Category=GameState)
	EGameState LastState = EGameState::Inactive;

	/**
	 * Current game result.
	 */
	UPROPERTY(VisibleInstanceOnly, Category=GameState)
	EGameResult GameResult = EGameResult::None;

	virtual bool PauseGame_Implementation() override;

	virtual bool UnpauseGame_Implementation() override;

	virtual bool ChangeInactivityReason_Implementation(const EGameInactivityReason NewInactivityReason) override;

	UFUNCTION()
	bool StartPreparationTimer();

	UFUNCTION()
	void HandlePreparationTimerFinished();

	UFUNCTION()
	bool StopPreparationTimer();

	UFUNCTION()
	bool PausePreparationTimer();

	UFUNCTION()
	bool UnPausePreparationTimer();

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	void PrintWarning(const FString& Message) const;

	void PrintLog(const FString& Message) const;

	static void GetGameStateName(FString& StateName, const EGameState State);

	static void GetInactivityReasonName(FString& ReasonName, const EGameInactivityReason Reason);

	static void GetGameResultName(FString& ResultName, const EGameResult Result);
#endif
};


