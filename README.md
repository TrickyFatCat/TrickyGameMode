# TrickyGameMode

A plugin with a custom game mode with different states.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

**At the moment, the package is compatible only with Unreal Engine 4.**

1. Download [**package file**](https://github.com/TrickyFatCat/TrickyAnimationComponents/releases/tag/v1.1);
2. Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_4.27\Engine\Plugins`;
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

#### Variables

#### Functions

#### Delegates

### PlayerControllerSession

#### Variables

#### Functions

## Quick setup

1. Create blueprint game mode inherited from GameModeSession class;
2. Adjust parameters as you want;
3. Choose this game mode in project settings;
4. Create blueprint player controller inherited from PlayerController class;
5. Adjust parameters as you want;
6. Create input action "Pause" in input settings;
7. Choose this player controller in project settings;
