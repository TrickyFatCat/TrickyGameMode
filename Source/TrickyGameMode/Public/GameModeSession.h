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
 * 
 */
UCLASS()
class TRICKYGAMEMODE_API AGameModeSession : public AGameModeBase
{
public:
	GENERATED_BODY()

	AGameModeSession();

	UPROPERTY(BlueprintAssignable, Category="GameMode")
	FOnStateChangedSignature OnStateChanged;

	UPROPERTY(BlueprintAssignable, Category="GameMode")
	FOnSessionFinishedSignature OnSessionFinished;

	virtual void StartPlay() override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;

	void StartSession();

	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	void FinishSession(const bool bIsVictory);

	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	float GetSessionElapsedTime() const;
	
	UFUNCTION(BlueprintCallable, Category="TrickyGameMode")
	float GetSessionRemainingTime() const;

private:
	// States
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameMode", meta=(AllowPrivateAccess))
	EGameModeState CurrentState = EGameModeState::Inactive;

	EGameModeState PreviousState = EGameModeState::Inactive;

	void SetState(EGameModeState NewState);

	// Preparation timer
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category="GameMode",
		meta=(AllowPrivateAccess, ClampMin="0"))
	float PreparationDuration = 3.f;

	UPROPERTY(BlueprintReadOnly, Category="GameMode", meta=(AllowPrivateAccess))
	FTimerHandle PreparationTimer;

	// Session timer
	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category="GameMode",
		meta=(AllowprivateAccess))
	bool bLimitSessionTime = false;

	UPROPERTY(EditAnywhere,
		BlueprintReadOnly,
		Category="GameMode",
		meta=(AllowPrivateAccess, EditCondition="bLimitSessionTime", ClampMIn="0"))
	float SessionDuration = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GameMode", meta=(AllowPrivateAccess, EditCondition="bLimitSessionTime"))
	bool bVictoryOnTimeOver = true;

	float TimeOnStart = 0.f;

	UPROPERTY(BlueprintReadOnly, Category="GameMode", meta=(AllowPrivateAccess))
	float FinalTime = 0.f;

	FTimerHandle SessionTimer;

	bool IsTimerActive(const FTimerHandle& TimerHandle) const;
};
