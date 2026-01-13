// Copyright Anton Vasserman, All Rights Reserved.


#include "StateTree/AV_StateTreePlayerComponent.h"

#include "StateTreeExecutionContext.h"
#include "StateTree/AV_StateTreePlayerComponentSchema.h"

//~ UStateTreeComponent

TSubclassOf<UStateTreeSchema> UAV_StateTreePlayerComponent::GetSchema() const
{
	return UAV_StateTreePlayerComponentSchema::StaticClass();
}

bool UAV_StateTreePlayerComponent::SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors)
{
	Context.SetCollectExternalDataCallback(FOnCollectStateTreeExternalData::CreateUObject(this, &UAV_StateTreePlayerComponent::CollectExternalData));
	return UAV_StateTreePlayerComponentSchema::SetContextRequirements(*this, Context, bLogErrors);
}
