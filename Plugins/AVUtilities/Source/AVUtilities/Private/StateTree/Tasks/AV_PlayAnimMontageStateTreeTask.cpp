// Copyright Anton Vasserman, All Rights Reserved.

#include "StateTree/Tasks/AV_PlayAnimMontageStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"

FAV_PlayAnimMontageStateTreeTask::FAV_PlayAnimMontageStateTreeTask()
{
	bShouldCallTick = false;
}

//~ FStateTreeTaskCommonBase

EStateTreeRunStatus FAV_PlayAnimMontageStateTreeTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
	
	UAnimInstance* AnimInstance = InstanceData.SkeletalMeshComponent->GetAnimInstance();
	
	if (!IsValid(InstanceData.AnimMontage.Get()))
	{
		return EStateTreeRunStatus::Failed;
	}

	UAnimMontage* AnimMontageLoaded = InstanceData.AnimMontage.LoadSynchronous();
	
	AnimInstance->Montage_Play(AnimMontageLoaded);
	if (InstanceData.bJumpToSection)
	{
		AnimInstance->Montage_JumpToSection(InstanceData.SectionName, AnimMontageLoaded);
	}

	return EStateTreeRunStatus::Succeeded;
}

#if WITH_EDITOR
FText FAV_PlayAnimMontageStateTreeTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting) const
{
	const FInstanceDataType* InstanceData = InstanceDataView.GetPtr<FInstanceDataType>();
	
	if (!InstanceData)
	{
		return FText::FromString(TEXT("Play Anim Montage"));
	}

	FString AnimMontageName = TEXT("None");
	if (InstanceData->AnimMontage)
	{
		AnimMontageName = InstanceData->AnimMontage->GetName();
	}

	FString JumpToSectionString = TEXT("");
	if (InstanceData->bJumpToSection)
	{
		JumpToSectionString = FString::Printf(TEXT(" from Section: %s"), *InstanceData->SectionName.ToString());
	}
	
	return FText::FromString(FString::Printf(TEXT("Play Anim Montage: %s%s"), *AnimMontageName, *JumpToSectionString));
}
#endif // WITH_EDITOR
