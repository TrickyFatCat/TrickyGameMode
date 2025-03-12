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

	UFUNCTION(BlueprintGetter, Category=GameState)
	FORCEINLINE EGameState GetInitialState() const { return InitialState; };

	UFUNCTION(BlueprintSetter, Category=GameState)
	void SetInitialState(const EGameState Value);

	UFUNCTION(BlueprintCallable, Category=GameState)
	FORCEINLINE EGameState GetCurrentState() const { return CurrentState; };

	UFUNCTION(BlueprintCallable, Category=GameState)
	FORCEINLINE EGameState GetLastState() const { return LastState; };

	virtual bool StartGame_Implementation() override;

	virtual bool FinishGame_Implementation(const EGameResult Result) override;

	virtual bool StopGame_Implementation(const EGameInactivityReason Reason) override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintGetter=GetInitialState, BlueprintSetter=SetInitialState, Category=GameState)
	EGameState InitialState = EGameState::Inactive;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetCurrentState, Category=GameState)
	EGameState CurrentState = EGameState::Inactive;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetLastState, Category=GameState)
	EGameState LastState = EGameState::Inactive;
	
	virtual bool PauseGame_Implementation() override;
	
	virtual bool UnpauseGame_Implementation() override;
};
