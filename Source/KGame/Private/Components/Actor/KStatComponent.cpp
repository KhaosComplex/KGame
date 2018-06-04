// Fill out your copyright notice in the Description page of Project Settings.

#include "KStatComponent.h"
#include "UnrealNetwork.h"


// Sets default values for this component's properties
UKStatComponent::UKStatComponent()
{
	// Make sure we replicate
	SetIsReplicated(true);

	// Extended setup
	fCachedMaxHealth = 100.f;
	fHealth = fCachedMaxHealth;


	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UKStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UKStatComponent, fHealth);
	DOREPLIFETIME(UKStatComponent, fCachedMaxHealth);
}

// Called when the game starts
void UKStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UKStatComponent::GetHealth() const
{
	return fHealth;
}

float UKStatComponent::GetMaxHealth() const
{
	return fCachedMaxHealth;
}

float UKStatComponent::GetHealthPercent() const
{
	return GetMaxHealth() > 0.0f ? GetHealth() / GetMaxHealth() : 1.f;
}

void UKStatComponent::OnRep_Health()
{
	BroadcastHealthChanged();
}

void UKStatComponent::BroadcastHealthChanged()
{
	OnHealthChangedDelegate.Broadcast(this);
	OnHealthChangedNativeDelegate.Broadcast(this);
}
