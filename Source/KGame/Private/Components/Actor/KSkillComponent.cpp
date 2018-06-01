// Fill out your copyright notice in the Description page of Project Settings.

#include "KSkillComponent.h"


// Sets default values for this component's properties
UKSkillComponent::UKSkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UKSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UKSkillComponent::ChangeFiringState(ESkillFiringState NextState)
{
	switch (NextState)
	{
	case ESkillFiringState::Idle:
		m_eSkillFiringState = ESkillFiringState::Idle;
		break;
	case ESkillFiringState::StartFiring:
		m_eSkillFiringState = ESkillFiringState::StartFiring;
		StartFiring();
		break;
	case ESkillFiringState::PreFire:
		m_eSkillFiringState = ESkillFiringState::PreFire;
		PreFire();
		break;
	case ESkillFiringState::DelayedPreFire:
		m_eSkillFiringState = ESkillFiringState::DelayedPreFire;
		GetWorld()->GetTimerManager().ClearTimer(m_FireTimer);
		DelayedPreFire();
		break;
	case ESkillFiringState::Fire:
		m_eSkillFiringState = ESkillFiringState::Fire;
		Fire();
		break;
	case ESkillFiringState::PostFire:
		m_eSkillFiringState = ESkillFiringState::PostFire;
		PostFire();
		break;
	case ESkillFiringState::DelayedPostFire:
		m_eSkillFiringState = ESkillFiringState::DelayedPostFire;
		GetWorld()->GetTimerManager().ClearTimer(m_FireTimer);
		DelayedPostFire();
		break;
	case ESkillFiringState::EndFiring:
		m_eSkillFiringState = ESkillFiringState::EndFiring;
		EndFiring();
		break;
	}
}

void UKSkillComponent::FireStandardShot()
{
	ChangeFiringState(ESkillFiringState::StartFiring);
}

void UKSkillComponent::StartFiring()
{
	ReceiveStartFiring();

	ChangeFiringState(ESkillFiringState::PreFire);
}

void UKSkillComponent::PreFire()
{
	ReceivePreFire();

	FTimerDelegate TransitionDelegate = FTimerDelegate::CreateUObject(this, &UKSkillComponent::ChangeFiringState, ESkillFiringState::DelayedPreFire);
	GetWorld()->GetTimerManager().SetTimer(m_FireTimer, TransitionDelegate, m_fPreFireDelay, false);
}

void UKSkillComponent::DelayedPreFire()
{
	ReceiveDelayedPreFire();

	ChangeFiringState(ESkillFiringState::Fire);
}

void UKSkillComponent::Fire()
{
	ReceiveFire();

	ChangeFiringState(ESkillFiringState::PostFire);
}

void UKSkillComponent::PostFire()
{
	ReceivePostFire();

	FTimerDelegate TransitionDelegate = FTimerDelegate::CreateUObject(this, &UKSkillComponent::ChangeFiringState, ESkillFiringState::DelayedPostFire);
	GetWorld()->GetTimerManager().SetTimer(m_FireTimer, TransitionDelegate, m_fPostFireDelay, false);
}

void UKSkillComponent::DelayedPostFire()
{
	ReceiveDelayedPostFire();

	ChangeFiringState(ESkillFiringState::EndFiring);
}

void UKSkillComponent::EndFiring()
{
	ReceiveEndFiring();

	ChangeFiringState(ESkillFiringState::Idle);
}

ESkillFiringState UKSkillComponent::GetSkillState() const
{
	return m_eSkillFiringState;
}