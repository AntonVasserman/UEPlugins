// Copyright Anton Vasserman, All Rights Reserved.


#include "Animation/AnimNotifies/AV_AnimNotify_SimulatePhysics.h"

#include "AV_CollisionProfileStatics.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/World.h"

//~ UAnimNotify

FString UAV_AnimNotify_SimulatePhysics::GetNotifyName_Implementation() const
{
	return FString::Printf(TEXT("Simulate Physics"));
}

void UAV_AnimNotify_SimulatePhysics::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	// Don't run the actual logic inside the editor...
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetWorld()) || !MeshComp->GetWorld()->IsGameWorld())
	{
		return;
	}

	MeshComp->SetSimulatePhysics(true);
	
	if (bSetCollisionProfileToRagdoll)
	{
		MeshComp->SetCollisionProfileName(UAV_CollisionProfileStatics::Ragdoll_ProfileName);	
	}
}
