// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Templates/SubclassOf.h"

#include "AV_AnimNotify_ApplyGameplayEffect.generated.h"

UCLASS(Meta = (DisplayName = "(DEPRECATED) Apply Gameplay Effect"), Deprecated)
class AVUTILITIESGAMEPLAYABILITIES_API UDEPRECATED_AV_AnimNotify_ApplyGameplayEffect : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify")
	TSubclassOf<UGameplayEffect> GameplayEffectClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify", Meta = (EditCondition = "GameplayEffectClass != nullptr", EditConditionHides))
	float GameplayEffectLevel = 1.f;
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
