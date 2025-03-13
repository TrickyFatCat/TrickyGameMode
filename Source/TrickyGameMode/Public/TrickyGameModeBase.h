// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameStateControllerInterface.h"
#include "GameFramework/GameModeBase.h"
#include "TrickyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TRICKYGAMEMODE_API ATrickyGameModeBase : public AGameModeBase, public IGameStateControllerInterface
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;

	UPROPERTY(BlueprintAssignable)
	FOnGameStartedDynamicSignature OnGameStarted;

	UPROPERTY(BlueprintAssignable)
	FOnGameFinishedDynamicSignature OnGameFinished;

	UPROPERTY(BlueprintAssignable)
	FOnGamePausedDynamicSignature OnGamePaused;

	UPROPERTY(BlueprintAssignable)
	FOnGameUnpausedDynamicSignature OnGameUnpaused;

	UPROPERTY(BlueprintAssignable)
	FOnGameStoppedDynamicSignature OnGameStopped;

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

	virtual bool PauseGame_Implementation() override;

	virtual bool UnpauseGame_Implementation() override;
	
	virtual bool ChangeInactivityReason_Implementation(const EGameInactivityReason NewInactivityReason) override;
};
