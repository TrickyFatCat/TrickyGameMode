# About

**TrickyGameState** provides a robust and flexible game state management system for Unreal Engine 5 prototype projects.

## Features

- **Game State Management** - Control your game's state with pre-defined states like Active, Inactive, Finished 
- **Game Session Control** - Easily start, stop, and finish game sessions with built-in timer functionality
- **Blueprint Support** - Full Blueprint integration with BlueprintCallable and BlueprintNativeEvent functions

## Installation

1. Copy the plugin folder into your project's `Plugins` directory.
2. Open your Unreal Engine project.
3. Enable the **TrickyGameMode** in the plugins menu.
4. Restart the editor.

## Functionality Overview

### GameStateControllerInterface

Provides a basic collection of functions for game state control

1. **`StartGame()`**
    - Transitions the game state to `Active`
    - Returns `true` if the game successfully started

2. **`FinishGame(EGameResult Result)`**
    - Transitions the game state to `Finished`
    - `Result` the result of finished game
    - Returns `true` if the game successfully finished

3. **`StopGame(EGameInactivityReason Reason)`**
    - Transitions the game state to `Inactive`
    - `Reason` of game inactivity
    - Returns `true` if the game successfully stopped

4. **`ChangeInactivityReason(EGameInactivityReason NewInactivityReason)`**
    - Updates the reason for game inactivity
    - Only applicable when game is in the `Inactive` state
    - Returns `true` if reason was successfully changed

5. **`StartPreparation()`**
    - Stops the game with `Preparation` inactivity reason
    - Returns `true` if game successfully stopped with `Preparation` reason

6. **`StartCutscene()`**
    - Stops the game with `Cutscene` inactivity reason
    - Returns `true` if game successfully stopped with `Cutscene` reason

7. **`StartTransition()`**
    - Stops the game with `Transition` inactivity reason
    - Returns `true` if game successfully stopped with `Transition` reason

8. **`GetGameState()`**
    - Returns the current game state (Active, Inactive, Finished, etc.)

9. **`GetGameResult()`**
    - Returns the current game result (Win, Loss, None, etc.)

10. **`GetGameInactivityReason()`**
    - Returns the current inactivity reason

11. **`GetGameElapsedTime()`**
    - Returns the time elapsed since the game started

12. **`GetGameRemainingTime()`**
    - Returns the remaining time for time-limited game

## TrickyGameModeBase

`TrickyGameModeBase` implements the `GameStateControllerInterface`.

### Properties:
1. **`PreparationDuration`**
    - Duration of preparation timer which is used during preparation phase
    - It won't start if it value less or equal zero
    - Game starts automatically when preparation timer ends

2. **`IsSessionTimeLimited`**
    - Determines if the game has a time limit

3. **`GameDuration`**
    - Duration for a time-limited game
    - Game finishes automatically when timer ends

4. **`DefaultTimeOverResult`**
    - A default game result when game is finished by timer

5. **`InitialInactivityReason`**
    - Default reason for initial inactive state

## TrickyGameModeLibrary

The `TrickyGameModeLibrary` provides convenient static functions for accessing and controlling game state from anywhere:

### Functions:

1. **`GetTrickyGameMode(WorldContextObject)`**
    - Returns the active `ATrickyGameModeBase` instance

2. **`StartGame()`**
    - Transitions the game state to `Active`
    - Returns `true` if the game successfully started

3. **`FinishGame(EGameResult Result)`**
    - Transitions the game state to `Finished`
    - `Result` the result of finished game
    - Returns `true` if the game successfully finished

4. **`StopGame(EGameInactivityReason Reason)`**
    - Transitions the game state to `Inactive`
    - `Reason` of game inactivity
    - Returns `true` if the game successfully stopped

5. **`ChangeInactivityReason(EGameInactivityReason NewInactivityReason)`**
    - Updates the reason for game inactivity
    - Only applicable when game is in the `Inactive` state
    - Returns `true` if reason was successfully changed

6. **`StartPreparation()`**
    - Stops the game with `Preparation` inactivity reason
    - Returns `true` if game successfully stopped with `Preparation` reason

7. **`StartCutscene()`**
    - Stops the game with `Cutscene` inactivity reason
    - Returns `true` if game successfully stopped with `Cutscene` reason

8. **`StartTransition()`**
    - Stops the game with `Transition` inactivity reason
    - Returns `true` if game successfully stopped with `Transition` reason

9. **`GetGameState()`**
    - Returns the current game state (Active, Inactive, Finished, etc.)

10. **`GetGameResult()`**
    - Returns the current game result (Win, Loss, None, etc.)

11. **`GetGameInactivityReason()`**
    - Returns the current inactivity reason

12. **`GetGameElapsedTime()`**
    - Returns the time elapsed since the game started

13. **`GetGameRemainingTime()`**
    - Returns the remaining time for time-limited game
