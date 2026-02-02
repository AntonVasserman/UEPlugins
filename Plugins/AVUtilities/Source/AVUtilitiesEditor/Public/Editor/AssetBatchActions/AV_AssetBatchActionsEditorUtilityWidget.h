// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"

#include "AV_AssetBatchActionsEditorUtilityWidget.generated.h"

UCLASS()
class AVUTILITIESEDITOR_API UAV_AssetBatchActionsEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UAV_AssetBatchActionsEditorUtilityWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
