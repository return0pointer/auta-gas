
#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangeSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangeSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangeSignature, float, NewMaxMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnAttributeChangedDelegate;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangeSignature OnHealthChange;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangeSignature OnMaxHealthChange;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangeSignature OnManaChange;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangeSignature OnMaxManaChange;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FMessageWidgetRowSignature OnMessageWidgetRowDelegate;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	void EffectTagApplied(const FGameplayTagContainer& AssetTags);
	void HealthChanged(const FOnAttributeChangeData& data);
	void MaxHealthChanged(const FOnAttributeChangeData& data);
	void ManaChanged(const FOnAttributeChangeData& data);
	void MaxManaChanged(const FOnAttributeChangeData& data);

	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}


