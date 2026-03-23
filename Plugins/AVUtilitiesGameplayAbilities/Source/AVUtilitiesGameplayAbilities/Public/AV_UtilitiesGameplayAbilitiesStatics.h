// Copyright Anton Vasserman, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CollisionShape.h"
#include "GameplayEffect.h"
#include "Engine/EngineTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AV_UtilitiesGameplayAbilitiesStatics.generated.h"

struct FHitResult;
class USkeletalMeshComponent;

/**
 *	Data used by the anim notify to execute gameplay effects.
 */
USTRUCT()
struct FAV_AnimNotifyGameplayEffectPayload
{
	GENERATED_BODY()
	
	// Gameplay effect to apply.
	UPROPERTY(EditDefaultsOnly, Category = "")
	TSubclassOf<UGameplayEffect> Class = nullptr;

	// Level of the gameplay effect to apply.
	UPROPERTY(EditDefaultsOnly, Category = "")
	int32 Level = 1;
	
	// Indicates that the effect uses magnitude calculation with set by caller values
	UPROPERTY(EditAnywhere, Category = "", Meta = (EditCondition = "Class != nullptr", EditConditionHides))
	bool bSetByCallerMagnitudeCalculation = false;
	
	// Magnitudes set by caller for the magnitude calculation
	UPROPERTY(EditAnywhere, Category = "", Meta = (EditCondition = "bSetByCallerMagnitudeCalculation == true", EditConditionHides))
	TMap<FGameplayTag, float> SetByCallerMagnitudes;
};

UENUM(BlueprintType)
enum class EAV_CollisionShapeType : uint8
{
	Line,
	Box,
	Sphere,
	Capsule
};

USTRUCT()
struct FAV_SweepParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "")
	FName SocketName = NAME_None;
	
	UPROPERTY(EditAnywhere, Category = "")
	FVector SocketOffset = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, Category = "")
	FVector SocketExtensionOffset = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere, Category = "")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	
	UPROPERTY(EditAnywhere, Category = "")
	EAV_CollisionShapeType CollisionShapeType = EAV_CollisionShapeType::Sphere;
	
	UPROPERTY(EditAnywhere, Category = "", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Box", EditConditionHides))
	FVector BoxHalfExtent = FVector::OneVector;
	
	UPROPERTY(EditAnywhere, Category = "", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Sphere", EditConditionHides))
	float SphereRadius = 60.f;
	
	UPROPERTY(EditAnywhere, Category = "", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Capsule", EditConditionHides))
	float CapsuleRadius = 40.f;
	
	UPROPERTY(EditAnywhere, Category = "", Meta = (EditCondition = "CollisionShapeType == EAV_CollisionShapeType::Capsule", EditConditionHides))
	float CapsuleHalfHeight = 40.f;
	
	UPROPERTY(EditAnywhere, Category = "")
	TSet<TEnumAsByte<ECollisionChannel>> CollisionChannelsToSweep = { ECC_Pawn };
	
	UPROPERTY(EditAnywhere, Category = "Debugs")
	bool bDrawDebugs = true;
};

/**
 * This is a library of helper functions specifically for this module, all of its functions shouldn't be exposed 
 * outside the module! 
 */
UCLASS(MinimalAPI)
class UAV_UtilitiesGameplayAbilitiesStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static TArray<FHitResult> PerformSweep(AActor* Owner, USkeletalMeshComponent* MeshComp, const FAV_SweepParams& SweepParams);
};
