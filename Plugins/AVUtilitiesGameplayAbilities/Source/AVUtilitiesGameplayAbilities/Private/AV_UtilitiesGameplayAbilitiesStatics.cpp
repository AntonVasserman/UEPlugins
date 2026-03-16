// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_UtilitiesGameplayAbilitiesStatics.h"

#include "KismetTraceUtils.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FHitResult> UAV_UtilitiesGameplayAbilitiesStatics::PerformSweep(AActor* Owner, USkeletalMeshComponent* MeshComp, const FAV_SweepParams& SweepParams)
{
	TArray<FHitResult> Hits;

	// Check that Engine and World are valid
	if (IsValid(GEngine) == false)
	{
		return Hits;
	}
	
	const UWorld* World = GEngine->GetWorldFromContextObject(Owner, EGetWorldErrorMode::LogAndReturnNull);
	if (IsValid(World) == false)
	{
		return Hits;	
	}

	const FTransform SocketTransform = MeshComp->GetSocketTransform(SweepParams.SocketName);
	const FVector Start = SocketTransform.TransformPosition(SweepParams.SocketExtensionOffset);
	const FVector End = Start;
	
	FCollisionShape CollisionShape;
	switch (SweepParams.CollisionShapeType)
	{
	case EAV_CollisionShapeType::Line:
		break;
	case EAV_CollisionShapeType::Box:
		CollisionShape = FCollisionShape::MakeBox(SweepParams.BoxHalfExtent);
		break;
	case EAV_CollisionShapeType::Sphere:
		CollisionShape = FCollisionShape::MakeSphere(SweepParams.SphereRadius);
		break;
	case EAV_CollisionShapeType::Capsule:
		CollisionShape = FCollisionShape::MakeCapsule(SweepParams.CapsuleRadius, SweepParams.CapsuleHalfHeight);
		break;
	default:
		checkNoEntry();
	}

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	for (ECollisionChannel CollisionChannel : SweepParams.CollisionChannelsToSweep)
	{
		ResponseParams.CollisionResponse.SetResponse(CollisionChannel, ECR_Block);	
	}

	bool const bHit = World->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, SweepParams.TraceChannel, CollisionShape, Params, ResponseParams);
	if (SweepParams.bDrawDebugs)
	{
#if ENABLE_DRAW_DEBUG
		switch (SweepParams.CollisionShapeType)
		{
		case EAV_CollisionShapeType::Line:
			DrawDebugLineTraceMulti(World, Start, End, EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		case EAV_CollisionShapeType::Box:
			DrawDebugBoxTraceMulti(World, Start, End, SweepParams.BoxHalfExtent, FQuat::Identity.Rotator(), EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		case EAV_CollisionShapeType::Sphere:
			DrawDebugSphereTraceMulti(World, Start, End, SweepParams.SphereRadius, EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		case EAV_CollisionShapeType::Capsule:
			DrawDebugCapsuleTraceMulti(World, Start, End, SweepParams.CapsuleRadius, SweepParams.CapsuleHalfHeight, FQuat::Identity.Rotator(), EDrawDebugTrace::ForDuration, bHit, Hits, FColor::Red, FColor::Green, 5.f);
			break;
		default:
			checkNoEntry();
		}
#endif
	}

	return Hits;
}
