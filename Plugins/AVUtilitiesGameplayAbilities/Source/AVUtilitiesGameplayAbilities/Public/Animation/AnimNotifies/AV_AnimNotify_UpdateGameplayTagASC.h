// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"

#include "AV_AnimNotify_UpdateGameplayTagASC.generated.h"

UENUM()
enum class EAV_GameplayTagUpdateType : uint8
{
	Set		UMETA(DisplayName = "Set", Description = "Sets Gameplay Tag to Character"),
	Remove	UMETA(DisplayName = "Remove", Description = "Removes Gameplay Tag from Character"),
};

UCLASS(Meta = (DisplayName = "Update Gameplay Tag (Ability System Component)"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AnimNotify_UpdateGameplayTagASC : public UAnimNotify
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|AnimNotify", Meta = (AllowPrivateAccess = "true"))
	EAV_GameplayTagUpdateType OperationType = EAV_GameplayTagUpdateType::Set;
	
	//~ UAnimNotify
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	//~ UObject
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif // WITH_EDITOR
};
