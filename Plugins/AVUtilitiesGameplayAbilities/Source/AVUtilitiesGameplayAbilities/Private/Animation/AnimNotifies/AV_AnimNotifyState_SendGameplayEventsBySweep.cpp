// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotifyState_SendGameplayEventsBySweep.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Engine.h"
#include "KismetTraceUtils.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif // WITH_EDITOR

TArray<FHitResult> UAV_AnimNotifyState_SendGameplayEventsBySweep::PerformSweep(AActor* Owner, USkeletalMeshComponent* MeshComp) const
{
	TArray<FHitResult> Hits;
	
	// Check that Engine and World are valid
	if (!IsValid(GEngine)) return Hits;
	const UWorld* World = GEngine->GetWorldFromContextObject(Owner, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World)) return Hits;
	
	const FTransform SocketTransform = MeshComp->GetSocketTransform(SocketName);
	const FVector Start = SocketTransform.GetLocation();
	const FVector ExtendedSocketDirection = SocketTransform.GetRotation().GetForwardVector() * SocketExtensionOffset;
	const FVector End = Start - ExtendedSocketDirection;
	
	FCollisionShape CollisionShape;
	switch (CollisionShapeType)
	{
	case EAV_CollisionShapeType::Line:
		break;
	case EAV_CollisionShapeType::Box:
		CollisionShape = FCollisionShape::MakeBox(BoxHalfExtent);
		break;
	case EAV_CollisionShapeType::Sphere:
		CollisionShape = FCollisionShape::MakeSphere(SphereRadius);
		break;
	case EAV_CollisionShapeType::Capsule:
		CollisionShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);
		break;
	default:
		checkNoEntry();
	}
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	for (ECollisionChannel CollisionChannel : CollisionChannelsToSweep)
	{
		ResponseParams.CollisionResponse.SetResponse(CollisionChannel, ECR_Block);	
	}
	
	bool const bHit = World->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, TraceChannel, CollisionShape, Params, ResponseParams);
	if (bDrawDebugs)
	{
#if ENABLE_DRAW_DEBUG
		switch (CollisionShapeType)
		{
		case EAV_CollisionShapeType::Line:
			DrawDebugLineTraceMulti(World, Start, End, EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		case EAV_CollisionShapeType::Box:
			DrawDebugBoxTraceMulti(World, Start, End, BoxHalfExtent, FQuat::Identity.Rotator(), EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		case EAV_CollisionShapeType::Sphere:
			DrawDebugSphereTraceMulti(World, Start, End, SphereRadius, EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		case EAV_CollisionShapeType::Capsule:
			DrawDebugCapsuleTraceMulti(World, Start, End, CapsuleRadius, CapsuleHalfHeight, FQuat::Identity.Rotator(), EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		default:
			checkNoEntry();
		}
#endif
	}
	
	return Hits;
}

void UAV_AnimNotifyState_SendGameplayEventsBySweep::SendEvents(AActor* Owner, TArray<FHitResult> Hits)
{
	const UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Owner);
	if (!IsValid(AbilitySystem)) return;
	
	for (FHitResult Hit : Hits)
	{
		if (!IsValid(Hit.GetActor())) continue;
		if (bSingleEventPerHitActor && HitActorsForWhomEventsSent.Contains(Hit.GetActor())) continue;
		
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddHitResult(Hit);
		
		FGameplayEventData Payload;
		Payload.ContextHandle = EffectContext;
		Payload.Instigator = Owner;
		Payload.Target = Hit.GetActor();
		
		if (GameplayEventTagForOwner != FGameplayTag::EmptyTag)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, GameplayEventTagForOwner, Payload);	
		}
		
		if (GameplayEventTagForHitActor != FGameplayTag::EmptyTag)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Hit.GetActor(), GameplayEventTagForHitActor, Payload);	
		}
		
		if (bSingleEventPerHitActor)
		{
			HitActorsForWhomEventsSent.Add(Hit.GetActor());
		}
	}
}

//~ UAnimNotifyState
FString UAV_AnimNotifyState_SendGameplayEventsBySweep::GetNotifyName_Implementation() const
{
	const UEnum* ChannelEnum = StaticEnum<ECollisionChannel>();
	const FString TraceString = ChannelEnum ? ChannelEnum->GetNameStringByValue(TraceChannel) : TEXT("UnknownTrace");

	TArray<FString> CollisionStrings;
	CollisionStrings.Reserve(CollisionChannelsToSweep.Num());
	for (const ECollisionChannel CollisionChannel : CollisionChannelsToSweep)
	{
		CollisionStrings.Add(ChannelEnum ? ChannelEnum->GetNameStringByValue(CollisionChannel) : TEXT("UnknownChannel"));
	}

	const FString CollisionsJoined = CollisionStrings.Num() > 0 ? FString::Join(CollisionStrings, TEXT("|")) : TEXT("None");

	FString Name = FString::Printf(TEXT("Send Gameplay Events by Trace: %s, with Collision: %s"), *TraceString, *CollisionsJoined);

	// Keep it timeline-friendly
	if (constexpr int32 MaxLen = 80;
		Name.Len() > MaxLen)
	{
		Name = Name.Left(MaxLen - 3) + TEXT("...");
	}

	return Name;
}

void UAV_AnimNotifyState_SendGameplayEventsBySweep::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	HitActorsForWhomEventsSent.Empty();
}

void UAV_AnimNotifyState_SendGameplayEventsBySweep::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	// Check for validity of mesh and owner
	if (!IsValid(MeshComp)) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!IsValid(Owner)) return;
	
	const TArray<FHitResult> Hits = PerformSweep(Owner, MeshComp);
	SendEvents(Owner, Hits);
}

#if WITH_EDITOR

EDataValidationResult UAV_AnimNotifyState_SendGameplayEventsBySweep::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = Super::IsDataValid(Context);

	if (GameplayEventTagForOwner == FGameplayTag::EmptyTag && GameplayEventTagForHitActor == FGameplayTag::EmptyTag)
	{
		Context.AddError(FText::FromString(TEXT("GameplayEventTags can't be Empty, at least one (Owner/HitActor) must be set")));
		Result = EDataValidationResult::Invalid;
	}
	
	return Result;
}

#endif // WITH_EDITOR