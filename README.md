# TrickyGameMode

A plugin with a custom game mode with different states.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

1. Download [**package file**](https://github.com/TrickyFatCat/TrickyGameMode/releases/);
2. Install the plugin either in your project or for all projects in engine:
   * Unzip the package into Plugins folder of your project, e.g. `D:\UnrealProjects\MyProject\Plugins`;
   * Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_5.0\Engine\Plugins`;
3. Restart the project;

In this case the plugin can be used for any blueprint project.

### C++ projects

1. Create the Plugins folder in the project directory;
2. Create the TrickyAnimationComponents folder in the Plugins folder;
3. Download the plugin source code into that folder;
4. Rebuild the project;

## Content

The plugin has actors:

1. GameModeSession;
2. PlayerControllerSession;

### GameModeSession

A basic game mode which has different states and timers implemented.

#### Variables

1. `CurrentState` - current state of the game;
2. `ManualStart` - if true the session will start automatically, else StartSession function must be called.
3. `PreparationDuration` - defines the time of the preparation state;
4. `PreparationTimer` - preparation timer handle;
5. `LimitSessionTime` - toggle if session time is limited or not;
6. `SessionDuration` - session length if its time is limited;
7. `VictoryOnTimeOver` - determines if session finished with victory when time is over;
8. `FinalTime` - the final time of the session when it finishes;

#### Functions

1. `StartSession` - starts the session;
2. `FinishSession` - finishes the session;
3. `StartPreparation` - starts a preparation timer;
4. `GetSessionElapsedTime` - returns session elapsed time;
5. `GetSessionRemainingTime` - returns session remaining time;

#### Delegates

1. `OnSessionChenged` - called when the state was changed;
2. `OnSessionFinished` - called when the session was finished;

### PlayerControllerSession

A player controller actor which has pause and GameModeSession states functionality;

#### Variables

1. `bShowCursorOnStart` - toggle if the mouse cursor must be shown when the session started;

#### Functions

1. `PauseGame` - pauses the game;
2. `OnGameModeStateChanged` - called when the session state was changed.
    * Override this function if you want to implement your controller functionality when the state was changed;

## Quick setup

1. Create blueprint game mode inherited from GameModeSession class;
2. Adjust parameters as you want;
3. Choose this game mode in project settings;
4. Create blueprint player controller inherited from PlayerController class;
5. Adjust parameters as you want;
6. Choose this player controller in project settings;
7. To pause and unpause game call the `PauseGame` function in the controller;
