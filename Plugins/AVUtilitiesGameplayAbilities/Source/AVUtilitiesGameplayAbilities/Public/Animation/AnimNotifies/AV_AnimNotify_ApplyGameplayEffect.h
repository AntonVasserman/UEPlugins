// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Templates/SubclassOf.h"

#include "AV_AnimNotify_ApplyGameplayEffect.generated.h"

class UGameplayEffect;

UCLASS(Meta = (DisplayName = "Apply Gameplay Effect"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotify_ApplyGameplayEffect : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Config|AnimNotify")
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Config|AnimNotify", Meta = (EditCondition = "GameplayEffectClass != nullptr", EditConditionHides))
	float GameplayEffectLevel = 1.f;
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
