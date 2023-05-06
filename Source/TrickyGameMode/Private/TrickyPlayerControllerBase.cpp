// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyPlayerControllerBase.h"


ATrickyPlayerControllerBase::ATrickyPlayerControllerBase()
{
}

void ATrickyPlayerControllerBase::BeginPlay()
{
	const UWorld* World = GetWorld();

	if (World)
	{
		ATrickyGameModeBase* GameMode = Cast<ATrickyGameModeBase>(World->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnStateChanged.AddDynamic(this, &ATrickyPlayerControllerBase::HandleGameStateChange);
		}
	}

	bShowMouseCursor = bShowCursorOnStart;
	SetTickableWhenPaused(true);

	Super::BeginPlay();
}

void ATrickyPlayerControllerBase::HandleGameStateChange_Implementation(EGameModeState NewState)
{
	auto ToggleInput = [&](const bool bEnableInput, const bool bShowCursor, const FInputModeDataBase& InputMode)
	{
		bEnableInput ? EnableInput(this) : DisableInput(this);
		bShowMouseCursor = bShowCursor;
		SetInputMode(InputMode);
	};

	switch (NewState)
	{
	case EGameModeState::InProgress:
		ToggleInput(true, bShowCursorOnStart, FInputModeGameOnly());
		break;

	case EGameModeState::Lose:
	case EGameModeState::Win:
		ToggleInput(false, true, FInputModeUIOnly());
		StopMovement();
		break;

	case EGameModeState::Pause:
		ToggleInput(true, true, FInputModeGameAndUI());
		break;

	default:
		ToggleInput(false, false, FInputModeUIOnly());
		break;
	}
}