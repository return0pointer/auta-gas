#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFount) const
{
	for (const FAuraInputAction& AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputTag == InputTag)
		{
			return AbilityInputAction.InputAction;
		}
	}

	if (bLogNotFount)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityAInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
