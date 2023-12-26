
#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeSignature, float, NewMaxMana);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangeSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangeSignature OnMaxHealthChange;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangeSignature OnManaChange;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangeSignature OnMaxManaChange;

protected:
	void HealthChanged(const FOnAttributeChangeData& data);
	void MaxHealthChanged(const FOnAttributeChangeData& data);
	void ManaChanged(const FOnAttributeChangeData& data);
	void MaxManaChanged(const FOnAttributeChangeData& data);
};
