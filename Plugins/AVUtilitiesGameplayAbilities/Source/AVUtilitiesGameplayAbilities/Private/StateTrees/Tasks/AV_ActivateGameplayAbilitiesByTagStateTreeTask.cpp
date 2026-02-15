// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTrees/Tasks/AV_ActivateGameplayAbilitiesByTagStateTreeTask.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "StateTreeAsyncExecutionContext.h"
#include "StateTreeExecutionContext.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbilityTypes.h"


bool FAV_ActivateGameplayAbilitiesByTagStateTreeTaskInstanceData::CheckAbilityThatHasEnded(const FAbilityEndedData& AbilityEndedData) const
{
	if (!IsValid(AbilityEndedData.AbilityThatEnded) || !AbilityEndedData.AbilitySpecHandle.IsValid())
	{
		return false;
	}
	
	return AbilityEndedData.AbilityThatEnded->GetAssetTags().HasAll(AbilityActivationTags);
}

EStateTreeRunStatus FAV_ActivateGameplayAbilitiesByTagStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (InstanceData.AbilitySystemComponent == nullptr)
	{
		return EStateTreeRunStatus::Failed;
	}
	
	InstanceData.bAbilityHasEnded = false;
	InstanceData.AbilitySpecHandle = FGameplayAbilitySpecHandle();
	
	FStateTreeWeakExecutionContext WeakExecutionContext = Context.MakeWeakExecutionContext();
	const FDelegateHandle Handle = InstanceData.AbilitySystemComponent->OnAbilityEnded.AddLambda([WeakExecutionContext](const FAbilityEndedData& AbilityEndedData) mutable
	{
		if (const FStateTreeStrongExecutionContext StrongExecutionContext = WeakExecutionContext.MakeStrongExecutionContext();
			StrongExecutionContext.IsValid())
		{
			if (FInstanceDataType* InstanceDataPtr = StrongExecutionContext.GetInstanceDataPtr<FInstanceDataType>();
				InstanceDataPtr->CheckAbilityThatHasEnded(AbilityEndedData))
			{
				InstanceDataPtr->bAbilityHasEnded = true;
				InstanceDataPtr->AbilityThatEnded = AbilityEndedData.AbilityThatEnded;
				InstanceDataPtr->AbilitySpecHandle = AbilityEndedData.AbilitySpecHandle;
				InstanceDataPtr->bAbilityWasCancelled = AbilityEndedData.bWasCancelled;
				
				if (IsValid(InstanceDataPtr->AbilitySystemComponent) && InstanceDataPtr->AbilityEndedDelegateHandle.IsValid())
				{
					InstanceDataPtr->AbilitySystemComponent->OnAbilityEnded.Remove(InstanceDataPtr->AbilityEndedDelegateHandle);
				}
	
				InstanceDataPtr->AbilityEndedDelegateHandle.Reset();
			}
		}
	});
	
	bool bActivated = false; 
	if (Handle.IsValid())
	{
		InstanceData.AbilityEndedDelegateHandle = Handle;
		bActivated = InstanceData.AbilitySystemComponent->TryActivateAbilitiesByTag(InstanceData.AbilityActivationTags);
	}
	
	return bActivated ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Failed;
}

EStateTreeRunStatus FAV_ActivateGameplayAbilitiesByTagStateTreeTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (InstanceData.bAbilityHasEnded == false || bShouldFinishStateWhenAbilityCompletes == false)
	{
		return EStateTreeRunStatus::Running;
	}
	
	if (InstanceData.bAbilityWasCancelled)
	{
		return bTreatCancelledAbilityAsSuccess ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
	}
	
	return EStateTreeRunStatus::Succeeded;
}

void FAV_ActivateGameplayAbilitiesByTagStateTreeTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	if (IsValid(InstanceData.AbilitySystemComponent) && InstanceData.AbilitySystemComponent->IsValidLowLevelFast())
	{
		if (InstanceData.AbilityEndedDelegateHandle.IsValid())
		{
			InstanceData.AbilitySystemComponent->OnAbilityEnded.Remove(InstanceData.AbilityEndedDelegateHandle);
			InstanceData.AbilityEndedDelegateHandle.Reset();
		}
		
		if (!InstanceData.bAbilityHasEnded && bShouldCancelAbilityWhenStateFinishes)
		{
			if (InstanceData.AbilitySpecHandle.IsValid())
			{
				InstanceData.AbilitySystemComponent->CancelAbilityHandle(InstanceData.AbilitySpecHandle);
			}
			else
			{
				InstanceData.AbilitySystemComponent->CancelAbilities(&InstanceData.AbilityActivationTags);
			}
		}		
	}
	
	InstanceData.AbilityEndedDelegateHandle.Reset();
	InstanceData.AbilityThatEnded.Reset();
}

#if WITH_EDITOR
FText FAV_ActivateGameplayAbilitiesByTagStateTreeTask::GetDescription(const FGuid& ID, const FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, const EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Activate Gameplay Abilities (by Tag)"));
	}

	return FText::FromString(FString::Printf(TEXT("Activate Gameplay Abilities with Tags: %s"), *InstanceData->AbilityActivationTags.ToStringSimple()));
}
#endif
