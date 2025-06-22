// Copyright Anton Vasserman, All Rights Reserved.


#include "Components/AV_CharacterFallComponent.h"

#include "AVMacros.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Tasks/Falling/AV_FallingTaskBase.h"
#include "Tasks/Landed/AV_LandedTaskBase.h"

DEFINE_LOG_CATEGORY(LogAV_CharacterFall);

// TODO: Add more logs...
static TAutoConsoleVariable CVarShowDebugAVCharacterFallComponent(
	TEXT("AVShowDebug.CharacterFallComponent"),
	false,
	TEXT("Shows the Debug information of the CharacterFallComponent class"),
	ECVF_Default);

UAV_CharacterFallComponent::UAV_CharacterFallComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAV_CharacterFallComponent::OnMovementModeChanged(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	if (const EMovementMode CurrentMovementMode = Character->GetCharacterMovement()->MovementMode;
		CurrentMovementMode == MOVE_Falling)
	{
		FallBeginZ = Character->GetActorLocation().Z;
	}
}

void UAV_CharacterFallComponent::Landed(const FHitResult& Hit)
{
	UE_LOG(LogAV_CharacterFall, Display, TEXT("%s::%hs: Landed with Fall Height: %f"), *GetClass()->GetName(), __FUNCTION__, FallHeight);
	if (CVarShowDebugAVCharacterFallComponent->GetBool())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Landed with Fall Height: %f"), FallHeight));
	}

	for (FAV_FallingConditionAndTasks ConditionToTasks : ConditionsToTasks)
	{
		// TODO: Consolidate this...
		FAV_FallRangeContext FallRangeContext;
		FallRangeContext.Character = OwnerCharacter;
		FallRangeContext.FallHeight = FallHeight;
		const EAV_FallRangeState FallRangeState = ConditionToTasks.FallRange.TestRange(FallRangeContext);

		// TODO: Maybe extract to methods "Inside" and "Outside"?
		if (FallRangeState == EAV_FallRangeState::Entered || FallRangeState == EAV_FallRangeState::Inside)
		{
			for (const UAV_LandedTaskBase* Task : ConditionToTasks.LandedTasks)
			{
				FAV_LandedTaskContext TaskContext;
				TaskContext.Character = OwnerCharacter;
				TaskContext.HitActor = Hit.GetActor();
				TaskContext.FallHeight = FallHeight;
				TaskContext.FallingComponent = this;
				
				Task->ExecuteTask(TaskContext);
			}
		}
	}
}

//~ UActorComponent Begin

void UAV_CharacterFallComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// We want to always evaluate FallHeight as we allow using it for multiple functionalities 
	if (OwnerCharacter->GetCharacterMovement()->MovementMode == MOVE_Falling)
	{
		FallHeight = FallBeginZ - GetOwner()->GetActorLocation().Z;

		// Use reference here because we change the struct's state
		for (FAV_FallingConditionAndTasks& ConditionToTasks : ConditionsToTasks)
		{
			// TODO: Consolidate this...
			FAV_FallRangeContext FallRangeContext;
			FallRangeContext.Character = OwnerCharacter;
			FallRangeContext.FallHeight = FallHeight;
			const EAV_FallRangeState FallRangeState = ConditionToTasks.FallRange.TestRange(FallRangeContext);

			switch (FallRangeState)
			{
			case EAV_FallRangeState::Exited:
				// TODO: Consolidate those somehow...
				for (const UAV_FallingTaskBase* Task : ConditionToTasks.FallingEnterTasks)
				{
					FAV_FallingTaskContext TaskContext;
					TaskContext.Character = OwnerCharacter;
					TaskContext.FallingComponent = this;
			
					Task->ExecuteTask(TaskContext);
				}
				break;
			case EAV_FallRangeState::Entered:
				// TODO: Consolidate those somehow...
				for (const UAV_FallingTaskBase* Task : ConditionToTasks.FallingExitTasks)
				{
					FAV_FallingTaskContext TaskContext;
					TaskContext.Character = OwnerCharacter;
					TaskContext.FallingComponent = this;
			
					Task->ExecuteTask(TaskContext);
				}
				break;
			AV_DEFAULT_CHECKNOENTRY
			}
		}
	}
	else // Not Falling anymore
	{
		// Use reference here because we change the struct's state
		for (FAV_FallingConditionAndTasks& ConditionToTasks : ConditionsToTasks)
		{
			// TODO: Consolidate this...
			FAV_FallRangeContext FallRangeContext;
			FallRangeContext.Character = OwnerCharacter;
			FallRangeContext.FallHeight = FallHeight;
			const EAV_FallRangeState FallRangeState = ConditionToTasks.FallRange.TestRange(FallRangeContext);
			
			if (FallRangeState == EAV_FallRangeState::Exited)
			{
				// TODO: Consolidate those somehow...
				for (const UAV_FallingTaskBase* Task : ConditionToTasks.FallingExitTasks)
				{
					FAV_FallingTaskContext TaskContext;
					TaskContext.Character = OwnerCharacter;
					TaskContext.FallingComponent = this;
			
					Task->ExecuteTask(TaskContext);
				}
			}
		}
	}
}

void UAV_CharacterFallComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = CastChecked<ACharacter>(GetOwner());
	OwnerCharacter->MovementModeChangedDelegate.AddDynamic(this, &UAV_CharacterFallComponent::OnMovementModeChanged);
	OwnerCharacter->LandedDelegate.AddDynamic(this, &UAV_CharacterFallComponent::Landed);
}

//~ UActorComponent End