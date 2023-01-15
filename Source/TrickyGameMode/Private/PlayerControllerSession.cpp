// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov


#include "PlayerControllerSession.h"

#include "Kismet/GameplayStatics.h"

APlayerControllerSession::APlayerControllerSession()
{
}

void APlayerControllerSession::BeginPlay()
{
	const UWorld* World = GetWorld();

	if (World)
	{
		AGameModeSession* GameMode = Cast<AGameModeSession>(World->GetAuthGameMode());

		if (GameMode)
		{
			GameMode->OnStateChanged.AddDynamic(this, &APlayerControllerSession::OnGameModeStateChanged);
		}
	}

	bShowMouseCursor = false;
	SetTickableWhenPaused(true);

	Super::BeginPlay();
}

void APlayerControllerSession::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding& PauseBinding = InputComponent->BindAction("Pause",
	                                                               IE_Pressed,
	                                                               this,
	                                                               &APlayerControllerSession::PauseGame);
	PauseBinding.bExecuteWhenPaused = true;
}

void APlayerControllerSession::OnGameModeStateChanged_Implementation(EGameModeState NewState)
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

	case EGameModeState::Finished:
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

void APlayerControllerSession::PauseGame()
{
	IsPaused()
		? UGameplayStatics::SetGamePaused(GetWorld(), false)
		: UGameplayStatics::SetGamePaused(GetWorld(), true);
}
