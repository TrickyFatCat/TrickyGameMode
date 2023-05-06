// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov


#include "TrickyPlayerControllerBase.h"

#include "Kismet/GameplayStatics.h"

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
			GameMode->OnStateChanged.AddDynamic(this, &ATrickyPlayerControllerBase::OnGameModeStateChanged);
		}
	}

	bShowMouseCursor = bShowCursorOnStart;
	SetTickableWhenPaused(true);

	Super::BeginPlay();
}

void ATrickyPlayerControllerBase::OnGameModeStateChanged_Implementation(EGameModeState NewState)
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
		break;

	case EGameModeState::Pause:
		ToggleInput(true, true, FInputModeGameAndUI());
		break;

	default:
		ToggleInput(false, false, FInputModeUIOnly());
		break;
	}
}

void ATrickyPlayerControllerBase::TogglePause()
{
	IsPaused()
		? UGameplayStatics::SetGamePaused(GetWorld(), false)
		: UGameplayStatics::SetGamePaused(GetWorld(), true);
}
