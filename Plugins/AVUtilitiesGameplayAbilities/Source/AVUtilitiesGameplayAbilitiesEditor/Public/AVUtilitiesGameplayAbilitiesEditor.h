#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAVUtilitiesGameplayAbilitiesEditorModule : public IModuleInterface
{
    //~ IModuleInterface
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
