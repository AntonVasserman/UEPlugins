// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AlphaBlend.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

#include "AV_AnimNotifyState_BlendOutCharacter.generated.h"

class ACharacter;
class UAnimSequenceBase;
class USkeletalMeshComponent;
struct FAnimNotifyEventReference;

UENUM(BlueprintType)
enum class EAV_BlendOutCondition : uint8
{
	Always,
	IfMoving,
	IfFalling,
	IfFallingOrFlying,
};

UCLASS(Meta = (DisplayName = "Blend Out (Character)"))
class AVUTILITIES_API UAV_AnimNotifyState_BlendOutCharacter : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	EAV_BlendOutCondition BlendOutCondition = EAV_BlendOutCondition::Always;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	FName BlendProfileName = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	float BlendOutTime = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	EAlphaBlendOption BlendOption = EAlphaBlendOption::HermiteCubic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	EMontageBlendMode BlendMode = EMontageBlendMode::Inertialization;
	
	static bool ShouldBlendOut(const ACharacter* InCharacter, const EAV_BlendOutCondition InBlendOutCondition);
	
	//~ UAnimNotifyState
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
};
