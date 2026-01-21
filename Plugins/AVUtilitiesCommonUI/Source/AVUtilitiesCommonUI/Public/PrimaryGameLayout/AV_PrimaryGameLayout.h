// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Widgets/CommonActivatableWidgetContainer.h" // IWYU pragma: keep

#include "AV_PrimaryGameLayout.generated.h"

#define UE_API AVUTILITIESCOMMONUI_API

class APlayerController;
class UClass;
class UCommonActivatableWidgetContainerBase;
class ULocalPlayer;
class UObject;

/**
 * The state of an async load operation for the UI.
 */
enum class EAsyncWidgetLayerState : uint8
{
	Canceled,
	Initialize,
	AfterPush
};

/**
 * The primary game UI layout of your game.  This widget class represents how to layout, push and display all layers
 * of the UI for a single player.  Each player in a split-screen game will receive their own primary game layout.
 */
UCLASS(MinimalAPI, Abstract, Meta = (DisableNativeTick))
class UAV_PrimaryGameLayout : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	static UE_API UAV_PrimaryGameLayout* GetPrimaryGameLayoutForPrimaryPlayer(const UObject* WorldContextObject);
	static UE_API UAV_PrimaryGameLayout* GetPrimaryGameLayout(APlayerController* PlayerController);
	static UE_API UAV_PrimaryGameLayout* GetPrimaryGameLayout(ULocalPlayer* LocalPlayer);
	
	UE_API UAV_PrimaryGameLayout(const FObjectInitializer& ObjectInitializer);

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerAsync(UPARAM(Meta = (Categories = "UI.Layer")) FGameplayTag LayerName, TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass)
	{
		return PushWidgetToLayerAsync<ActivatableWidgetT>(LayerName, ActivatableWidgetClass, [](EAsyncWidgetLayerState, ActivatableWidgetT*) {});
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerAsync(UPARAM(Meta = (Categories = "UI.Layer")) FGameplayTag LayerName, TSoftClassPtr<UCommonActivatableWidget> ActivatableWidgetClass, TFunction<void(EAsyncWidgetLayerState, ActivatableWidgetT*)> StateFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		TSharedPtr<FStreamableHandle> StreamingHandle = StreamableManager.RequestAsyncLoad(ActivatableWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateWeakLambda(this,
			[this, LayerName, ActivatableWidgetClass, StateFunc]()
			{
				ActivatableWidgetT* Widget = PushWidgetToLayer<ActivatableWidgetT>(LayerName, ActivatableWidgetClass.Get(), [StateFunc](ActivatableWidgetT& WidgetToInit) {
					StateFunc(EAsyncWidgetLayerState::Initialize, &WidgetToInit);
				});

				StateFunc(EAsyncWidgetLayerState::AfterPush, Widget);
			})
		);

		// Setup a cancel delegate so that we can resume input if this handler is canceled.
		StreamingHandle->BindCancelDelegate(FStreamableDelegate::CreateWeakLambda(this,
			[this, StateFunc]()
			{
				StateFunc(EAsyncWidgetLayerState::Canceled, nullptr);
			})
		);

		return StreamingHandle;
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayer(UPARAM(Meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UClass* ActivatableWidgetClass)
	{
		return PushWidgetToLayer<ActivatableWidgetT>(LayerName, ActivatableWidgetClass, [](ActivatableWidgetT&) {});
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayer(UPARAM(Meta = (Categories = "UI.Layer")) FGameplayTag LayerName, UClass* ActivatableWidgetClass, TFunctionRef<void(ActivatableWidgetT&)> InitInstanceFunc)
	{
		static_assert(TIsDerivedFrom<ActivatableWidgetT, UCommonActivatableWidget>::IsDerived, "Only CommonActivatableWidgets can be used here");

		if (UCommonActivatableWidgetContainerBase* Layer = GetLayerWidget(LayerName))
		{
			return Layer->AddWidget<ActivatableWidgetT>(ActivatableWidgetClass, InitInstanceFunc);
		}

		return nullptr;
	}

	// Find the widget if it exists on any of the layers and remove it from the layer.
	UE_API void FindAndRemoveWidgetFromLayers(UCommonActivatableWidget* ActivatableWidget);

	// Get the layer widget for the given layer tag.
	UE_API UCommonActivatableWidgetContainerBase* GetLayerWidget(UPARAM(Meta = (Categories = "UI.Layer")) FGameplayTag LayerName) const;

protected:
	/** Register a layer that widgets can be pushed onto. */
	UFUNCTION(BlueprintCallable, Category = "Layer")
	UE_API void RegisterLayer(UPARAM(Meta = (Categories = "UI.Layer")) FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget);

private:
	// The registered layers for the primary layout.
	UPROPERTY(Transient, Meta = (Categories = "UI.Layer"))
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> Layers;
};

#undef UE_API
