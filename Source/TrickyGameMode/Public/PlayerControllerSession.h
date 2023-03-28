// MIT License Copyright (c) Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameModeSession.h"
#include "PlayerControllerSession.generated.h"

/**
 * A player controller which has pause and GameModeSession states functionality.
 */
UCLASS()
class TRICKYGAMEMODE_API APlayerControllerSession : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerSession();

protected:
	virtual void BeginPlay() override;

	/**
	 * Toggle if the mouse cursor must be shown when the session started.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controller")
	bool bShowCursorOnStart = false;

	/**
	 * Called when the game state was changed.
	 */
	UFUNCTION(BlueprintNativeEvent, Category="Controller")
	void OnGameModeStateChanged(EGameModeState NewState);

	/**
	 * Pauses the game
	 */
	UFUNCTION(BlueprintCallable, Category="Cotroller")
	void PauseGame();
};
