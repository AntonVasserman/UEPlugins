# Primary Game Layout Usage

1. Custom PrimaryGameLayout Widget
    1.  Create a Widget (Blueprint Class) inheriting from AV_PrimaryGameLayout.
    2.  Add 'CommonActivatableWidgetContainerBase's (Stacks or other) as your Layers and Register them in the 'OnInitialized' Event
    3.	Create 'UI.Layer.X' GameplayTags respectively to each Layer in the PrimaryGameLayout Widget.
2. Go to 'Project Settings' → 'Primary Game Layout Settings' and update 'Primary Game Layout Class' to use your newly created PrimaryGameLayout Widget.
3. Custom GameInstance Class
   1. Create the C++ inheriting from 'UGameInstance'.
   2. Override 'AddLocalPlayer' Notifying to the PrimaryGameLayoutSubsystem that a Player was added.
   3. Go to 'Project Settings' → 'Maps & Modes' and update the 'Game Instance' → 'Game Instance Class' to use your custom GameInstance Class.

Sample code for the custom UGameInstance:

```cpp
int32 UTDS_GameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 ReturnVal = Super::AddLocalPlayer(NewPlayer, UserId);
	if (ReturnVal != INDEX_NONE)
	{
		GetSubsystem<UAV_PrimaryGameLayoutSubsystem>()->NotifyPlayerAdded(NewPlayer);
	}
	
	return ReturnVal;
}
```