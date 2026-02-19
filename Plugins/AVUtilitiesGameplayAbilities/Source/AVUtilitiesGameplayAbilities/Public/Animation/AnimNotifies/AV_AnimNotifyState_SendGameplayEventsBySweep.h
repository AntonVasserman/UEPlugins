// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CollisionShape.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"

#include "AV_AnimNotifyState_SendGameplayEventsBySweep.generated.h"

struct FHitResult;
class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EAV_CollisionShapeType : uint8
{
	Line,
	Box,
	Sphere,
	Capsule
};

UCLASS(Meta = (DisplayName = "Send Gameplay Event By Sweep"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotifyState_SendGameplayEventsBySweep : public UAnimNotifyState
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Event")
	FGameplayTag GameplayEventTagForOwner;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Event")
	FGameplayTag GameplayEventTagForHitActor;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Event")
	bool bSingleEventPerHitActor = false;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep")
	FName SocketName = NAME_None;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep")
	float SocketExtensionOffset = 40.f;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep")
	EAV_CollisionShapeType CollisionShapeType = EAV_CollisionShapeType::Sphere;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Box", EditConditionHides))
	FVector BoxHalfExtent = FVector::OneVector;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Sphere", EditConditionHides))
	float SphereRadius = 60.f;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Capsule", EditConditionHides))
	float CapsuleRadius = 40.f;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Capsule", EditConditionHides))
	float CapsuleHalfHeight = 40.f;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Sweep")
	TSet<TEnumAsByte<ECollisionChannel>> CollisionChannelsToSweep = { ECC_Pawn };
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Debugs")
	bool bDrawDebugs = true;
	
	UPROPERTY(Transient)
	TSet<AActor*> HitActorsForWhomEventsSent;
	
	TArray<FHitResult> PerformSweep(AActor* Owner, USkeletalMeshComponent* MeshComp) const;
	void SendEvents(AActor* Owner, TArray<FHitResult> Hits);
	
	//~ UAnimNotifyState
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
