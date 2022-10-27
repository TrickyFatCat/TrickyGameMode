// MIT License Copyright (c) 2022 Artyom "Tricky Fat Cat" Volkov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameModeSession.h"
#include "PlayerControllerSession.generated.h"

/**
 * 
 */
UCLASS()
class TRICKYGAMEMODE_API APlayerControllerSession : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerSession();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controller")
	bool bShowCursorOnStart = false;
	
	UFUNCTION(BlueprintNativeEvent, Category="Controller")
	void OnGameModeStateChanged(EGameModeState NewState);

	UFUNCTION()
	void PauseGame();
};
