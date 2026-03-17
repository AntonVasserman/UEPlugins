// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Templates/SubclassOf.h"

#include "AV_AnimNotify_ApplyGameplayEffects.generated.h"

/**
 *	Data used by the anim notify to execute gameplay effects.
 */
USTRUCT()
struct FAV_AnimNotify_ApplyGameplayEffects_GameplayEffect
{
	GENERATED_BODY()
	
	// Gameplay effect to apply.
	UPROPERTY(EditDefaultsOnly, Category = "")
	TSubclassOf<UGameplayEffect> Class = nullptr;

	// Level of the gameplay effect to apply.
	UPROPERTY(EditDefaultsOnly, Category = "")
	int32 Level = 1;
};

UCLASS(Meta = (DisplayName = "Apply Gameplay Effects"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotify_ApplyGameplayEffects : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify")
	TArray<FAV_AnimNotify_ApplyGameplayEffects_GameplayEffect> GameplayEffects;
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
