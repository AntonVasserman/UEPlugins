// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

#include "AV_AnimNotifyState_AddGameplayTagASC.generated.h"

UCLASS(Meta = (DisplayName = "Add Gameplay Tag (Ability System Component)"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotifyState_AddGameplayTagASC : public UAnimNotifyState
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify")
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify")
	int32 Count = 1;
	
	UPROPERTY(EditAnywhere, Category = "Config|AnimNotify")
	bool bRemoveOnExit = false;
	
	//~ UAnimNotifyState Begin
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
