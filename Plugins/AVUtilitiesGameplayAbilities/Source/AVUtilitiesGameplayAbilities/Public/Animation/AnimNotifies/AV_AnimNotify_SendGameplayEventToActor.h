// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AV_AnimNotify_SendGameplayEventToActor.generated.h"

UCLASS(Meta = (DisplayName = "Send Gameplay Event to Actor"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotify_SendGameplayEventToActor : public UAnimNotify
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	FGameplayTag EventTag;
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
