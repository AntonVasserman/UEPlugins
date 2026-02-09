// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTree/Tasks/AV_SpawnSoundAtLocationStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundAttenuation.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundConcurrency.h"

FAV_SpawnSoundAtLocationStateTreeTask::FAV_SpawnSoundAtLocationStateTreeTask()
{
	bShouldCallTick = false;
}

//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_SpawnSoundAtLocationStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (!IsValid(InstanceData.Sound.Get()))
	{
		return EStateTreeRunStatus::Failed;
	}

	USoundBase* SoundBaseLoaded = InstanceData.Sound.LoadSynchronous();
	
	UGameplayStatics::SpawnSoundAtLocation(
		Context.GetWorld(), 
		SoundBaseLoaded, 
		InstanceData.Location,
		InstanceData.Rotation,
		InstanceData.VolumeMultiplier,
		InstanceData.PitchMultiplier,
		InstanceData.StartTime,
		InstanceData.AttenuationSettings ? InstanceData.AttenuationSettings.LoadSynchronous() : nullptr,
		InstanceData.ConcurrencySettings ? InstanceData.ConcurrencySettings.LoadSynchronous() : nullptr,
		InstanceData.bAutoDestroy);
	
	return EStateTreeRunStatus::Succeeded;
}

#if WITH_EDITOR
FText FAV_SpawnSoundAtLocationStateTreeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Spawn Sound at Location"));
	}

	FString SoundName = TEXT("None");
	if (InstanceData->Sound)
	{
		SoundName = InstanceData->Sound->GetName();
	}

	return FText::FromString(FString::Printf(TEXT("Spawn Sound: %s at Location: %s"), *SoundName, *InstanceData->Location.ToString()));
}
#endif // WITH_EDITOR

