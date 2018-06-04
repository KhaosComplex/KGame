// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KStatComponent.generated.h"

// Multicast delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const class UKStatComponent*, StatComponent);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KGAME_API UKStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKStatComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

///////////////////
// Health
///////////////////
public:
	/** Returns our Health. */
	UFUNCTION(BlueprintPure, Category = "Health")
	virtual float GetHealth() const;
	/** Returns our CachedMaxHealth. */
	UFUNCTION(BlueprintPure, Category = "Health")
	virtual float GetMaxHealth() const;
	/** Returns our Health % off MaxHealth. */
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	/** Returns our native on health changed delegate. */
	DECLARE_EVENT_OneParam(AKCharacter, FOnHealthChangedNative, const class UKStatComponent*);
	FOnHealthChangedNative& OnHealthChangedNative() { return OnHealthChangedNativeDelegate; }
	/** Returns our blueprint on health changed delegate. */
	FOnHealthChanged& OnHealthChanged() { return OnHealthChangedDelegate; }

protected:
	/** Called as we're replicating our health. */
	UFUNCTION()
	virtual void OnRep_Health();
	/** Calls our multicast delegates to broadcast our health changed. */
	void BroadcastHealthChanged();

	/** Health. */
	UPROPERTY(EditDefaultsOnly, DisplayName = "Health", Category = "Health", ReplicatedUsing = OnRep_Health)
	float fHealth;
	/** Initial Max Health cached. */
	UPROPERTY(EditDefaultsOnly, DisplayName = "MaxHealth", Category = "Health", ReplicatedUsing = OnRep_Health)
	float fCachedMaxHealth;

private:
	/** Native On Health Changed Delegate. */
	FOnHealthChangedNative OnHealthChangedNativeDelegate;
	/** Blueprint On Health Changed Delegate. */
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChangedDelegate;
	
};
