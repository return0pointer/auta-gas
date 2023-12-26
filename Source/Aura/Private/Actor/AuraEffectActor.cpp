#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* AbilitySystem = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (AbilitySystem == nullptr) return;
	
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystem->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystem->MakeOutgoingSpec(
		GameplayEffectClass, 1.0f, EffectContextHandle);
	AbilitySystem->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
}
