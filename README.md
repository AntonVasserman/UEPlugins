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

<details>
  <summary>Change log</summary>

- 1.2: Upgraded to Unreal Engine 5.7.
- 1.1: Updated Fall Height evaluation logic to start evaluating only when falling and descending
- 1.0: Added the Character Fall Component and its relevant supporting classes

</details>

## AV Level Prototyping (AVLevelPrototyping)

This is a plugin containing assets used for Level Prototyping that I use across all my personal projects.

<details>
  <summary>Change log</summary>

- 0.8: Removed usage of non cross-platform \_\_FUNCTIONW\_\_ macro
- 0.7: Added more Material colors taken from new Template Projects and Target Static Mesh
- 0.6: Fixed Object Redirectors
- 0.5: Upgraded to Unreal Engine 5.7.
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

<details>
  <summary>Change log</summary>

- 0.15: Added MathLibrary and AnimNotify_SimulatePhysics
- 0.14: Removed usage of non cross-platform \_\_FUNCTIONW\_\_ macro
- 0.13: Added KismetFunctionLibrary with Extended Print String functions
- 0.12: Fixes to Volume Classes
- 0.11: Added Basic Volume Class
- 0.10:
  - All StateTree Condition and Tasks Icon updates
  - Play AnimMontage State Tree Task removed SoftClassPtr
- 0.9:
  - StateTree Task to provide the Skeletal Mesh Component
  - Updated Play AnimMontage StateTree Task to use the Skeletal Mesh Component
- 0.8: Added new StateTree classes:
  - StateTree Condition to check if two Gameplay Tags are equal
  - StateTree Task to Spawn Sound at Location
- 0.7: 
  - Added new AnimNotifies:
    - AV_AnimNotifyState_BlendOutCharacter
    - AV_AnimNotifyState_CharacterCapsuleLerp
  - First iteration of "Asset Batch Actions" Editor Utility Widget
- 0.6: Added UMG Class:
  - CreateUserWidgetAsync 
- 0.5: Added StateTree Classes:
  - PlayerController StateTree Component and ComponentSchema
  - Object Implements Interface StateTree Task
  - Play AnimMontage StateTree Task
  - Play Force Feedback StateTree Task
- 0.4: Upgraded to Unreal Engine 5.7.
- 0.3: Updated class prefixes
- 0.2: Update to Unreal Engine 5.6
- 0.1: Initial Release:
  - Collision Profile Statics containing all profile names for collisions
  - Draw Debug Statics containing a function to draw a named directional arrow

</details>

## AV Utilities Library for the CommonUI Plugin (AVUtilitiesCommonUI)

This is a plugin of a module that contains utilities and extensions for the CommonUI Plugin.

This includes small parts taken from the 'CommonGame' and 'UIExtension' plugins from Lyra by Epic Games. Until those plugins are available on Marketplace,
in which case they will be removed from this repository and used instead.

<details>
  <summary>Change log</summary>

- 0.3: [TODO] Added content from 'UIExtension' plugin from Lyra by Epic Games
- 0.2: Added ConfirmationWidget logic from 'CommonGame' plugin from Lyra by Epic Games
- 0.1: Initial Release:
  - Added initial and refactored content from the 'CommonGame' plugin from Lyra by Epic Games suitable for single-player games

</details>

## AV Utilities Library for the Gameplay Abilities Plugin (AVUtilitiesGameplayAbilities)

This is a plugin of a module that contains utilities and extensions for the Gameplay Abilities Plugin.

<details>
  <summary>Change log</summary>

- 0.11:
  - Added AnimNotify ApplyGameplayEffects (plural)
  - Deprecated AnimNotify ApplyGameplayEffect
- 0.10:
  - Improved AnimNotifyState SendGameplayEventsBySweep
  - Added AnimNotify ApplyGameplayEffectBySweep
- 0.9: 
  - Removed usage of non cross-platform \_\_FUNCTIONW\_\_ macro 
  - Added AbilitySet
  - Added ResourceStateChanged delegate
- 0.8: Added Resource States (Full, Normal, Critical, Depleted)
- 0.7: Minor improvement to AnimNotifyState SendGameplayEventsBySweep
- 0.6: Added Generic Resource classes:
  - ResourceAttributeSet
  - ResourceComponent
  - ResourceViewModel
- 0.5:
  - All StateTree Condition and Tasks Icon updates
  - Added new State Tree Tasks:
    - Activate Gameplay Abilities by Tag
    - Cancel Gameplay Abilities by Tag
- 0.4: Improvements for Anim Notify State to Send Gameplay Events to Sweeped actors
- 0.3:
  - Anim Notify State to Send Gameplay Events to Sweeped actors
  - Removed StateTree Evaluator for Ability System Component in favor of a Global StateTree Task
- 0.2: Added new AnimNotifies:
  - AV_AnimNotify_ApplyGameplayEffect
  - AV_AnimNotify_SendGameplayEventToActor
  - AV_AnimNotify_UpdateGameplayTagASC
  - AV_AnimNotifyState_AddGameplayTagASC
- 0.1: Initial Release:
  - Added StateTree Classes:
    - StateTree Condition to check if a Gameplay Tag is present
    - StateTree Evaluator to extract an Ability System Component from the context Actor
    - StateTree Task to apply a Gameplay Effect
    - StateTree Task to add a Gameplay Tag

</details>