// Copyright Anton Vasserman, All Rights Reserved.


#include "AV_AbilitySystemBlueprintLibrary.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Abilities/GameplayAbility.h"

APawn* UAV_AbilitySystemBlueprintLibrary::GetAvatarPawnFromAbility(const UGameplayAbility* Ability, TSubclassOf<APawn> PawnClass, bool bChecked)
{
	if (!Ability)
	{
		if (bChecked)
		{
			checkf(false, TEXT("%hs: Ability is null"), __FUNCTION__);
		}
		
		return nullptr;
	}

	AActor* AvatarActor = Ability->GetAvatarActorFromActorInfo();
	APawn* Pawn = bChecked ? CastChecked<APawn>(AvatarActor) : Cast<APawn>(AvatarActor);
	
	if (!PawnClass)
	{
		return Pawn;
	}

	if (Pawn && Pawn->IsA(PawnClass))
	{
		return Pawn;
	}

	if (bChecked)
	{
		checkf(false, TEXT("%hs: AvatarPawn (%s) is not of class %s"), __FUNCTION__, *GetNameSafe(Pawn), *GetNameSafe(PawnClass.Get()));
	}

	return nullptr;
}
