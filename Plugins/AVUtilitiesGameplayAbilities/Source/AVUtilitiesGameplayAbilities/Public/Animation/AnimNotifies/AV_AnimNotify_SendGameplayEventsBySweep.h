// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AV_UtilitiesGameplayAbilitiesStatics.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AV_AnimNotify_SendGameplayEventsBySweep.generated.h"

UCLASS(Meta = (DisplayName = "Send Gameplay Events by Sweep"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotify_SendGameplayEventsBySweep : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Event")
	TArray<FGameplayTag> GameplayEventsForOwner;
	
	// Indicates if an event to the owner should be sent per hit actor or just once for all hit actors.
	// Important note, if it's a single event than 'HitActor' won't be set.
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Event")
	bool bSendSingleEventToOwner = false;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Event")
	TArray<FGameplayTag> GameplayEventsForHitActor;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify", Meta = (DisplayName = "Sweep"))
	FAV_SweepParams SweepParams;
	
	void SendEvents(AActor* Owner, TArray<FHitResult> Hits);
	
	//~ UAnimNotifyState
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
