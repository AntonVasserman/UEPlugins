// Copyright Anton Vasserman, All Rights Reserved.


#include "Engine/AV_Volume.h"

#include "AV_CollisionProfileStatics.h"
#include "Components/BoxComponent.h"
#include "Engine/AV_VolumeAction.h"
#include "Engine/AV_VolumeFilter.h"

#if WITH_EDITORONLY_DATA
#include "Components/BillboardComponent.h"
#endif // WITH_EDITORONLY_DATA

AAV_Volume::AAV_Volume()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(GetRootComponent());

	BoxComponent->SetCollisionProfileName(UAV_CollisionProfileStatics::OverlapAllDynamic_ProfileName);
	
#if WITH_EDITORONLY_DATA
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	BillboardComponent->SetupAttachment(GetRootComponent());
	
	BillboardComponent->SetSprite(Sprite);
	BillboardComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
#endif // WITH_EDITORONLY_DATA
}

bool AAV_Volume::IsInVolume(const FVector& WorldLocation) const
{
	/*
	 * We are comparing the World Location point here as a Local Point relative to the Box Component.
	 * 
	 * Example:
	 * Box World Position = (100, 50, 0)
	 * Rotation = Yaw + 90
	 * Extent = (20, 10, 5)
	 * 
	 * Point in the World = (95, 60, 2)
	 * 
	 * Mapping it into the Boxes Local Space would result in: (10, 5, 2)
	 * (We subtract rotation P_World - C_World, and then undo rotation)
	 * 
	 * Finally we do a test where we check if the Local Point is within the Box Extent
	 */
	const FVector LocalPoint = BoxComponent->GetComponentTransform().InverseTransformPosition(WorldLocation);
	const FVector LocalExtent = BoxComponent->GetUnscaledBoxExtent();

	return FMath::Abs(LocalPoint.X) <= LocalExtent.X
		 && FMath::Abs(LocalPoint.Y) <= LocalExtent.Y
		 && FMath::Abs(LocalPoint.Z) <= LocalExtent.Z;
}

float AAV_Volume::GetClosestPointOnVolume(const FVector& WorldLocation, FVector& OutClosestPointOnVolume) const
{
	return BoxComponent->GetClosestPointOnCollision(WorldLocation, OutClosestPointOnVolume);
}

void AAV_Volume::BoxComponent_OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool bShouldExecuteActions = true;
	
	for (const UAV_VolumeFilter* VolumeFilter : VolumeFilters)
	{
		if (VolumeFilter->Filter(OtherActor, OtherComp) == false)
		{
			bShouldExecuteActions = false;
			break;
		}
	}
	
	if (bShouldExecuteActions)
	{
		FAV_VolumeActionContext Context;
		Context.OverlappedVolume = this;
		Context.OverlappedComponent = OverlappedComponent;
		Context.OtherActor = OtherActor;
		Context.OtherComp = OtherComp;
		
		for (const UAV_VolumeAction* VolumeAction : VolumeActions)
		{
			if (IsValid(VolumeAction))
			{
				VolumeAction->Execute(Context);	
			}
		}
	}
}

void AAV_Volume::BoxComponent_OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
}

//~ AActor

void AAV_Volume::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	BoxComponent->SetBoxExtent(VolumeExtent / 2.f);
	BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, BoxComponent->GetUnscaledBoxExtent().Z));
	
#if WITH_EDITORONLY_DATA
	BillboardComponent->SetSprite(Sprite);
	BillboardComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
#endif // WITH_EDITORONLY_DATA
}

void AAV_Volume::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BoxComponent_OnComponentBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::BoxComponent_OnComponentEndOverlap);
}
