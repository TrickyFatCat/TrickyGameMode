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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionFinishedSignature, bool, bIsVictory);

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

	UFUNCTION(BlueprintGetter, Category="TrickyGameMode")
	float GetPreparationDuration() const;

	UFUNCTION(BlueprintSetter, Category="TrickyGameMode")
	void SetPreparationDuration(const float Value);
	
	void StartSession();

	void FinishSession(const bool bIsVictory);

private:
	// States
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameMode", meta=(AllowPrivateAccess))
	EGameModeState CurrentState = EGameModeState::Inactive;

	EGameModeState PreviousState = EGameModeState::Inactive;

	void SetState(const EGameModeState& NewState);

	// Preparation timer
	UPROPERTY(EditAnywhere,
		BlueprintGetter=GetPreparationDuration,
		BlueprintSetter=SetPreparationDuration,
		Category="GameMode",
		meta=(AllowPrivateAccess, ClampMin="0"))
	float PreparationDuration = 3.f;

	UPROPERTY(BlueprintReadOnly, Category="GameMode", meta=(AllowPrivateAccess))
	FTimerHandle PreparationTimer;

	bool IsTimerActive(const FTimerHandle& TimerHandle) const;


};