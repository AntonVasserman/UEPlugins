// Copyright Anton Vasserman, All Rights Reserved.


#include "UI/ViewModel/AV_ResourceViewModel.h"

#include "AVUtilitiesGameplayAbilities.h"

void UAV_ResourceViewModel::SetCurrentValue(float NewCurrentValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentValue, NewCurrentValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetValuePercentage);
	}
}

void UAV_ResourceViewModel::SetMaxValue(float NewMaxValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxValue, NewMaxValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetValuePercentage);
	}
}

float UAV_ResourceViewModel::GetValuePercentage() const
{
	if (MaxValue == 0.f)
	{
		AV_LOG_UTILSGAS_EXTENDED(Warning, "MaxValue is 0. Returning 0!");
		return 0.f;
	}

	return CurrentValue / MaxValue;
}
