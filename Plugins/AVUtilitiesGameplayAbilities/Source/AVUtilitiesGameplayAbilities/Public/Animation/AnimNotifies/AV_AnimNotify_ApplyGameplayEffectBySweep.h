// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AV_UtilitiesGameplayAbilitiesStatics.h"
#include "GameplayEffect.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Templates/SubclassOf.h"

#include "AV_AnimNotify_ApplyGameplayEffectBySweep.generated.h"

struct FAV_SweepParams;

UCLASS(Meta = (DisplayName = "(DEPRECATED) Apply Gameplay Effect By Sweep"), Deprecated)
class AVUTILITIESGAMEPLAYABILITIES_API UDEPRECATED_AV_AnimNotify_ApplyGameplayEffectBySweep : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Effect")
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Effect", Meta = (EditCondition = "GameplayEffectClass != nullptr", EditConditionHides))
	float GameplayEffectLevel = 1.f;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Effect", Meta = (EditCondition = "GameplayEffectClass != nullptr", EditConditionHides))
	bool bSetByCallerMagnitudeCalculation = false;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify|Effect", Meta = (EditCondition = "bSetByCallerMagnitudeCalculation == true", EditConditionHides))
	TMap<FGameplayTag, float> SetByCallerMagnitudes;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify", Meta = (DisplayName = "Sweep"))
	FAV_SweepParams SweepParams;
	
	void ApplyEffect(AActor* Owner, TArray<FHitResult> Hits);
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
