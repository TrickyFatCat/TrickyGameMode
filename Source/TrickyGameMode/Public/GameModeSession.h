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
	Active,
	Pause,
	GameOver
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChangedSignature, EGameModeState, NewState);

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

	virtual void StartPlay() override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;

	virtual bool ClearPause() override;
	
private:
	// States

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GameMode", meta=(AllowPrivateAccess))
	EGameModeState CurrentState = EGameModeState::Inactive;

	EGameModeState PreviousState = EGameModeState::Inactive;

	void SetState(const EGameModeState& NewState);
};
