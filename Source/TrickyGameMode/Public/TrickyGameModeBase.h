// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameStateControllerInterface.h"
#include "GameFramework/GameModeBase.h"
#include "TrickyGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPreparationTimerStartedDynamicSignature, float, Duration);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPreparationTimerStoppedDynamicSignature, float, ElapsedTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimerStartedDynamicSignature, float, Duration);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimerStoppedDynamicSignature, float, ElapsedTime);

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

	/**
	 * Triggered when a preparation timer started.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPreparationTimerStartedDynamicSignature OnPreparationTimerStarted;

	/**
	 * Triggered when a preparation timer stopped.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnPreparationTimerStoppedDynamicSignature OnPreparationTimerStopped;
	
	/**
	 * Triggered when a game timer started.
	 * @warning called only if bIsGameTimeLimited == true
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameTimerStartedDynamicSignature OnGameTimerStarted;

	/**
	 * Triggered when a game timer stopped.
	 * @warning called only if bIsGameTimeLimited == true
	 */
	UPROPERTY(BlueprintAssignable)
	FOnGameTimerStoppedDynamicSignature OnGameTimerStopped;

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE float GetPreparationDuration() const { return PreparationDuration; }

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetPreparationDuration(const float Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE FTimerHandle GetPreparationTimerHandle() const { return PreparationTimerHandle; }

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE bool GetIsSessionTimeLimited() const { return bIsSessionTimeLimited; }

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetIsSessionTimeLimited(const bool Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE float GetGameDuration() const { return GameDuration; }

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetGameDuration(const float Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE FTimerHandle GetSessionTimerHandle() const { return GameTimerHandle; }

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameResult GetDefaultTimeOverResult() const { return DefaultTimeOverResult; }

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetDefaultTimeOverResult(const EGameResult Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameInactivityReason GetInitialInactivityReason() const { return InitialInactivityReason; }

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetInitialInactivityReason(const EGameInactivityReason Value);

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameInactivityReason GetCurrentInactivityReason() const { return CurrentInactivityReason; }

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameState GetCurrentState() const { return CurrentState; };

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameState GetLastState() const { return LastState; };

	virtual bool StartGame_Implementation() override;

	virtual bool FinishGame_Implementation(const EGameResult Result) override;

	virtual bool StopGame_Implementation(const EGameInactivityReason Reason) override;

	virtual bool StartPreparation_Implementation() override;

	virtual bool StartCutscene_Implementation() override;

	virtual bool StartTransition_Implementation() override;

	virtual EGameState GetGameState_Implementation() const override;

	virtual EGameResult GetGameResult_Implementation() const override;

	virtual EGameInactivityReason GetGameInactivityReason_Implementation() const override;
	
	virtual float GetGameElapsedTime_Implementation() const override;

	virtual float GetGameRemainingTime_Implementation() const override;

protected:
	/**
	 * Calculates the game result when the game time is over.
	 * @warting it's used only when bIsGameTimeLimited == true.
	 * 
	 * @return The result of the game when time is over.
	 */
	UFUNCTION(BlueprintNativeEvent, Category=GameState)
	EGameResult CalculateTimeOverResult();

	virtual EGameResult CalculateTimeOverResult_Implementation() { return DefaultTimeOverResult; }

private:
	/**
	 * An inactivity reason which will be used when the game mode initialized
	 */
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetInitialInactivityReason,
		BlueprintSetter=SetInitialInactivityReason,
		Category=GameState)
	EGameInactivityReason InitialInactivityReason = EGameInactivityReason::Transition;

	/**
	 * Determines the duration of the preparation phase in seconds before the game transitions to the active state.
	 * @warning This value cannot be less than 0.0.
	 */
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetPreparationDuration,
		BlueprintSetter=SetPreparationDuration,
		Category=GameState,
		meta=(ClampMin="0.0", UIMin="0.0"))
	float PreparationDuration = 3.0f;

	UPROPERTY(BlueprintGetter=GetPreparationTimerHandle, Category=GameState)
	FTimerHandle PreparationTimerHandle;

	/**
	 * Defines whether the game session is time-limited.
	 */
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetIsSessionTimeLimited,
		BlueprintSetter=SetIsSessionTimeLimited,
		Category=GameState)
	bool bIsSessionTimeLimited = false;

	/**
	 * Defines duration of the game timer.
	 * @warning Is used only if bIsSessionTimeLimited == true.
	 */
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetGameDuration,
		BlueprintSetter=SetGameDuration,
		Category=GameState,
		meta=(ClampMin="1.0", UIMin="1.0", EditCondition="bIsSessionTimeLimited"))
	float GameDuration = 120.0f;

	/**
	 * Defines the default outcome of the game when the session time expires.
	 * @warting Is used only if bIsSessionTimeLimited == true.
	 */
	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetDefaultTimeOverResult,
		BlueprintSetter=SetDefaultTimeOverResult,
		Category=GameState,
		meta=(EditCondition="bIsSessionTimeLimited"))
	EGameResult DefaultTimeOverResult = EGameResult::Win;

	UPROPERTY(BlueprintGetter=GetSessionTimerHandle, Category=GameState)
	FTimerHandle GameTimerHandle;

	float StartGameTime = 0.f;

	/**
	 * Current inactivity reason.
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

	/**
	 * Starts the preparation timer.
	 *
	 * @return True if the timer was successfully started.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool StartPreparationTimer();

	UFUNCTION()
	void HandlePreparationTimerFinished();

	/**
	 * Stops the preparation timer.
	 *
	 * @return True if the preparation timer was successfully stopped.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool StopPreparationTimer();

	/**
	 * Pauses the preparation timer.
	 *
	 * @return True if the preparation timer was successfully paused.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool PausePreparationTimer();

	/**
	 * Unpauses the preparation timer.
	 *
	 * @return True if the preparation timer is successfully unpaused.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool UnPausePreparationTimer();

	/**
	 * Starts the game timer.
	 *
	 * @return True if the game timer was successfully started;.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool StartGameTimer();

	/**
	 * Stops the game timer.
	 *
	 * @return True if the game timer was successfully stopped.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool StopGameTimer();

	/**
	 * Pauses the game timer.
	 *
	 * @return True if the game timer was successfully paused.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool PauseGameTimer() const;

	/**
	 * Unpauses the game timer.
	 *
	 * @return True if the game timer was successfully unpaused.
	 */
	UFUNCTION(BlueprintCallable, Category=GameState)
	bool UnPauseGameTimer() const;

	UFUNCTION()
	void HandleGameTimerFinished();

#if WITH_EDITOR || !UE_BUILD_SHIPPING
	void PrintWarning(const FString& Message) const;

	void PrintLog(const FString& Message) const;

	static void GetGameStateName(FString& StateName, const EGameState State);

	static void GetInactivityReasonName(FString& ReasonName, const EGameInactivityReason Reason);

	static void GetGameResultName(FString& ResultName, const EGameResult Result);
#endif
};
