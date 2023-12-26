#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChange.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChange.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	Super::BindCallbackToDependencies();

	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(
		this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(
		this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(
		this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(
		this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& data)
{
	OnHealthChange.Broadcast(data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& data)
{
	OnMaxHealthChange.Broadcast(data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& data)
{
	OnManaChange.Broadcast(data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& data)
{
	OnMaxManaChange.Broadcast(data.NewValue);
}
