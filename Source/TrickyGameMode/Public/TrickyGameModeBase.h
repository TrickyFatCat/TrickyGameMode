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
	 * Called when the game was successfully started.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameStartedDynamicSignature OnGameStarted;

	/**
	 * Called when the game was successfully finished.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameFinishedDynamicSignature OnGameFinished;

	/**
	 * Called when the game was successfully paused.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGamePausedDynamicSignature OnGamePaused;

	/**
	 * Called when the game was successfully unpaused.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameUnpausedDynamicSignature OnGameUnpaused;

	/**
	 * Called when the game was successfully stopped.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameStoppedDynamicSignature OnGameStopped;

	/**
	 * Called when the inactivity reason successfully changed.
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
	/**
	 * Initial inactivity state.
	 */
	UPROPERTY(EditInstanceOnly,
		BlueprintGetter=GetInitialInactivityReason,
		BlueprintSetter=SetInitialInactivityReason,
		Category=GameState)
	EGameInactivityReason InitialInactivityReason = EGameInactivityReason::Transition;

	/**
	 * Current inactivity state.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetCurrentInactivityReason, Category=GameState)
	EGameInactivityReason CurrentInactivityReason = EGameInactivityReason::Transition;

	/**
	 * Current game state.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetCurrentState, Category=GameState)
	EGameState CurrentState = EGameState::Inactive;

	/**
	 * Last game state which was before pause.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetLastState, Category=GameState)
	EGameState LastState = EGameState::Inactive;

	/**
	 * Current game result when it finishes.
	 */
	UPROPERTY(VisibleAnywhere)
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
