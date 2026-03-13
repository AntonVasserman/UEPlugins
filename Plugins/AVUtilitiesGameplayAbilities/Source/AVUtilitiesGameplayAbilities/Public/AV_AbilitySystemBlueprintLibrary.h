// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SubclassOf.h"

#include "AV_AbilitySystemBlueprintLibrary.generated.h"

class APawn;
class UGameplayAbility;

UCLASS(Meta = (ScriptName = "AbilitySystemLibrary"))
class AVUTILITIESGAMEPLAYABILITIES_API UAV_AbilitySystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Returns the Ability's Avatar as a Pawn, optionally filtered by PawnClass.
	 * - If PawnClass is null -> returns Avatar cast to APawn (or nullptr)
	 * - If PawnClass is set -> returns Avatar pawn only if it IsA(PawnClass)
	 */
	UFUNCTION(BlueprintPure, Category="GameplayAbilities", Meta = (DefaultToSelf = "Ability", DeterminesOutputType = "PawnClass", AdvancedDisplay = "bChecked"))
	static APawn* GetAvatarPawnFromAbility(const UGameplayAbility* Ability, TSubclassOf<APawn> PawnClass, bool bChecked = false);
};
