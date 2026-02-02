// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotifyState_BlendOutCharacter.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimNotifyQueue.h"
#include "Animation/Skeleton.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UAV_AnimNotifyState_BlendOutCharacter::ShouldBlendOut(const ACharacter* InCharacter, const EAV_BlendOutCondition InBlendOutCondition)
{
	switch (InBlendOutCondition)
	{
	case EAV_BlendOutCondition::Always:
		return true;
	case EAV_BlendOutCondition::IfMoving:
		return InCharacter->GetCharacterMovement()->GetCurrentAcceleration().IsNearlyZero(0.1f) == false;
	case EAV_BlendOutCondition::IfFalling:
		return InCharacter->GetCharacterMovement()->IsFalling();
	case EAV_BlendOutCondition::IfFallingOrFlying:
		return InCharacter->GetCharacterMovement()->IsFalling() || InCharacter->GetCharacterMovement()->MovementMode == MOVE_Flying;
	default:
		checkNoEntry();
		return false;
	}
}

//~ UAnimNotifyState

FString UAV_AnimNotifyState_BlendOutCharacter::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("BlendOut: %s"), *StaticEnum<EAV_BlendOutCondition>()->GetNameStringByValue(static_cast<int64>(BlendOutCondition)));
}

void UAV_AnimNotifyState_BlendOutCharacter::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	const ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character == nullptr)
	{
		return;
	}

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	const UAnimMontage* AnimMontage = Cast<UAnimMontage>(Animation);

	if (AnimMontage == nullptr)
	{
		return;
	}

	if (ShouldBlendOut(Character, BlendOutCondition) == false)
	{
		return;
	}

	FAlphaBlendArgs AlphaBlendArgs;
	AlphaBlendArgs.BlendTime = BlendOutTime;
	AlphaBlendArgs.BlendOption = BlendOption;
	
	FMontageBlendSettings BlendOutSettings(AlphaBlendArgs);
	BlendOutSettings.BlendProfile = AnimInstance->CurrentSkeleton->GetBlendProfile(BlendProfileName);
	BlendOutSettings.BlendMode = BlendMode;
	
	AnimInstance->Montage_StopWithBlendSettings(BlendOutSettings, AnimMontage);
}
