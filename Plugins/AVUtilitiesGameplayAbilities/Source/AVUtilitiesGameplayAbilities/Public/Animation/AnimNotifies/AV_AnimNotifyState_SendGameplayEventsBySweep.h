// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AV_UtilitiesGameplayAbilitiesStatics.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"

#include "AV_AnimNotifyState_SendGameplayEventsBySweep.generated.h"

struct FHitResult;
class USkeletalMeshComponent;

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
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify", Meta = (DisplayName = "Sweep"))
	FAV_SweepParams SweepParams;
	
	UPROPERTY(Transient)
	TSet<AActor*> HitActorsForWhomEventsSent;
	
	void SendEvents(AActor* Owner, TArray<FHitResult> Hits);
	
	//~ UAnimNotifyState
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
