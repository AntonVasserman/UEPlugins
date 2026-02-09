// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "AV_PlayAnimMontageStateTreeTask.generated.h"

class UAnimMontage;
class USkeletalMeshComponent;

USTRUCT()
struct AVUTILITIES_API FAV_PlayAnimMontageStateTreeTaskInstanceData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Context")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	TSoftObjectPtr<UAnimMontage> AnimMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Parameter", Meta = (EditCondition = "AnimMontage != nullptr", EditConditionHides))
	bool bJumpToSection = false;

	UPROPERTY(EditAnywhere, Category = "Parameter", Meta = (EditCondition = "AnimMontage != nullptr && bJumpToSection == true", EditConditionHides))
	FName SectionName = NAME_None;
};

USTRUCT(Meta = (DisplayName = "Play Anim Montage"))
struct AVUTILITIES_API FAV_PlayAnimMontageStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FAV_PlayAnimMontageStateTreeTask();
	
	using FInstanceDataType = FAV_PlayAnimMontageStateTreeTaskInstanceData;

	//~ FStateTreeTaskCommonBase
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FName GetIconName() const override { return FName("Node.Animation"); }
	virtual FColor GetIconColor() const override { return UE::StateTree::Colors::Magenta; }
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};
