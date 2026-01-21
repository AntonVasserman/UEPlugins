// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "AV_PrimaryGameLayoutSettings.generated.h"

class UAV_PrimaryGameLayout;

/**
 * This class is responsible for storing and managing the configurations of the primary game layout.
 */
UCLASS(Config = Game, DefaultConfig, Meta = (DisplayName = "Primary Game Layout Settings"))
class AVUTILITIESCOMMONUI_API UAV_PrimaryGameLayoutSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category = "", Meta = (AllowedClasses = "/Script/AVUtilitiesCommonUI.AV_PrimaryGameLayout"))
	TSoftClassPtr<UAV_PrimaryGameLayout> PrimaryGameLayoutClass;
};
