// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AV_UtilitiesGameplayAbilitiesStatics.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AV_AnimNotify_ApplyGameplayEffectsBySweep.generated.h"

UCLASS(Meta = (DisplayName = "Apply Gameplay Effects By Sweep"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotify_ApplyGameplayEffectsBySweep : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify")
	TArray<FAV_AnimNotifyGameplayEffectPayload> GameplayEffects;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify", Meta = (DisplayName = "Sweep"))
	FAV_SweepParams SweepParams;
	
	void ApplyEffects(AActor* Owner, TArray<FHitResult> Hits);
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
