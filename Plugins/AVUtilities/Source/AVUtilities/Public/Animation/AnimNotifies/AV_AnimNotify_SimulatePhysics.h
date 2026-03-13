// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AV_AnimNotify_SimulatePhysics.generated.h"

struct FAnimNotifyEventReference;
class UAnimSequenceBase;
class USkeletalMeshComponent;

UCLASS(Meta = (DisplayName = "Simulate Physics"))
class AVUTILITIES_API UAV_AnimNotify_SimulatePhysics : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	bool bSetCollisionProfileToRagdoll = false;
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
