// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeSession.generated.h"

UENUM(BlueprintType)
enum class EGameModeState : uint8
{
	Inactive,
	Preparation,
	InProgress,
	Pause,
	Finished
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChangedSignature, EGameModeState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionFinishedSignature, bool, bIsVictory, float, FinalTime);

/**
 * A basic game mode which has different states and timers implemented.
 */
UCLASS()
class TRICKYGAMEMODE_API AGameModeSession : public AGameModeBase
{
public:
	GENERATED_BODY()

	AGameModeSession();

	/**
	 * Called when the state was changed.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyGameMode")
	FOnStateChangedSignature OnStateChanged;

	/**
	 * Called when the session was finished.
	 */
	UPROPERTY(BlueprintAssignable, Category="TrickyGameMode")
	FOnSessionFinishedSignature OnSessionFinished;

	virtual void StartPlay() override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;

	/**
	 * Starts the session.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	void StartSession();

	/**
	 * Finishes the session.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	void FinishSession(const bool bIsVictory);

	/**
	 * Starts a preparation timer.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	void StartPreparation();

	/**
	 * Returns session elapsed time.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	float GetSessionElapsedTime() const;

	/**
	 * Returns session remaining time.
	 */
	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	float GetSessionRemainingTime() const;

	/**
	 * Returns if the session must be start manually.
	 */
	UFUNCTION(BlueprintGetter, Category="TrickyGameMode")
	bool IsManualStart() const;

private:
	// States
	/**
	 * Current state of the game.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TrickyGameMode", meta=(AllowPrivateAccess))
	EGameModeState CurrentState = EGameModeState::Inactive;

	EGameModeState PreviousState = EGameModeState::Inactive;

	void SetState(EGameModeState NewState);

	/**
	 * If true the session will start automatically, else StartSession function must be called.
	 */
	UPROPERTY(EditAnywhere, BlueprintGetter = IsManualStart , Category="TrickyGameMode", meta=(AllowPrivateAccess))
	bool bManualStart = false;

	// Preparation timer
	/**
	 * Defines the time of the Preparation state.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category="TrickyGameMode",
		meta=(AllowPrivateAccess, ClampMin="0"))
	float PreparationDuration = 3.f;

	/**
	 * Preparation timer handle.
	 */
	UPROPERTY(BlueprintReadOnly, Category="TrickyGameMode", meta=(AllowPrivateAccess))
	FTimerHandle PreparationTimer;

	// Session timer
	/**
	 * Toggles if session time is limited or not.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category="TrickyGameMode",
		meta=(AllowprivateAccess))
	bool bLimitSessionTime = false;

	/**
	 * Session length if its time limited.
	 */
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category="TrickyGameMode",
		meta=(AllowPrivateAccess, EditCondition="bLimitSessionTime", ClampMIn="0"))
	float SessionDuration = 30.f;

	/**
	 * Determines if session finished with victory when time is over.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TrickyGameMode",
		meta=(AllowPrivateAccess, EditCondition="bLimitSessionTime"))
	bool bVictoryOnTimeOver = true;

	float TimeOnStart = 0.f;

	/**
	 * The final time of the session when it finishes.
	 */
	UPROPERTY(BlueprintReadOnly, Category="TrickyGameMode", meta=(AllowPrivateAccess))
	float FinalTime = 0.f;

	FTimerHandle SessionTimer;

	bool IsTimerActive(const FTimerHandle& TimerHandle) const;
};
