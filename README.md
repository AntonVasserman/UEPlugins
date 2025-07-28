# UEPlugins

Centralized Repository for all my personal Unreal Engine Plugins

# Installation Guide

Since my plugins aren't Marketplace plugins, adding them needs to be done manually.

To do so follow the next steps:
1. Choose which Plugin you want to use from the `PluginsPackaged` folder, and extract the plugin from its ZIP format.
2. Copy the plugin folder inside (e.g. if you unpacked `AVCharacterFallV1.0`, inside it is the `AVCharacterFall` folder)
3. Paste it in your projects Plugins folder (e.g. if you have a project `CursedLands` go to `CursedLands/Plugins`)
4. Right-click on your project's `uproject` file and choose `Generate Visual Studio Project Files`
5. In your project's build C# file (e.g. `CursedLands.Build.cs`) add the plugin as a Public/Private dependency
6. [OPTIONAL] If for any reason the plugin isn't visible, in the Unreal Editor go to `Edit -> Plugins` and make sure the plugin is checked

# Current Plugins
## AV Character Fall (AVCharacterFall)

This is a plugin that adds the Character Fall System with the CFC (Character Fall Component) that can be attached to Actors.

This Component provides two main functionalities:
1. Executing certain tasks when entering/exiting certain fall height thresholds.
2. Executing certain tasks upon landing with from a certain fall height.

Current Version: 1.1

<details>
  <summary>Change log</summary>

- 1.1: Updated Fall Height evaluation logic to start evaluating only when falling and descending
- 1.0: Added the Character Fall Component and its relevant supporting classes

</details>

## AV Level Prototyping (AVLevelPrototyping)

This is a plugin containing assets used for Level Prototyping that I use across all my personal projects.

Current Version: 0.4

<details>
  <summary>Change log</summary>

- 0.4: Added 2 Sample Maps
- 0.3: Update to Unreal Engine 5.6
- 0.2: Improved the Teleporter Actor (taking GASP as an example)
- 0.1: Initial Release:
  - Multiple Grid Materials to be used for level blockouts
  - A Level Block actor for level blockouts
  - A Teleporter actor for teleporting a character from one point to another

</details>

## AV Utilities Library (AVUtilities)

This is a plugin of a module that contains all my shared code that will be used across all my personal projects.

Current Version: 0.3

<details>
  <summary>Change log</summary>

- 0.3: Updated class prefixes
- 0.2: Update to Unreal Engine 5.6
- 0.1: Initial Release:
  - Collision Profile Statics containing all profile names for collisions
  - Draw Debug Statics containing a function to draw a named directional arrow

</details>