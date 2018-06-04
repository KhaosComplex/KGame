// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KSkill.h"
#include "KSkillComponent.generated.h"

UENUM(BlueprintType)
enum class ESkillFiringState : uint8
{
	Idle,
	StartFiring,
	PreFire,
	DelayedPreFire,
	Fire,
	PostFire,
	DelayedPostFire,
	EndFiring,
};


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KGAME_API UKSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKSkillComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Handles all the logic for firing a standard shot. */
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireStandardShot();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartFiring();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceivePreFire();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveDelayedPreFire();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveFire();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceivePostFire();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveDelayedPostFire();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveEndFiring();


	/** Returns our Skill State. */
	UFUNCTION(BlueprintPure, Category = "State")
	virtual ESkillFiringState GetSkillState() const;

	FTimerHandle m_FireTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Pre Fire Delay", Category = "Firing")
	float m_fPreFireDelay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, DisplayName = "Post Fire Delay", Category = "Firing")
	float m_fPostFireDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, DisplayName = "Skills", Category = "Skills", Instanced)
	TArray<UKSkill*> Skills;

	UPROPERTY(BlueprintReadWrite, DisplayName = "Current Skill Index", Category = "Skills")
	uint8 nCurrentSkill;

	UFUNCTION(BlueprintPure, Category = "Skills")
	virtual UKSkill* GetCurrentSkill() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Called after we enter the firing state. */
	virtual void StartFiring();
	/** Pre fire logic. */
	virtual void PreFire();
	/** Pre fire logic that occurs after the delay. */
	virtual void DelayedPreFire();
	/** Officially Fire. */
	virtual void Fire();
	/** Post fire logic. */
	virtual void PostFire();
	/** Post fire logic that occurs after the delay. */
	virtual void DelayedPostFire();
	/** Called before leave the firing state. */
	virtual void EndFiring();

	UPROPERTY(BlueprintReadOnly, DisplayName = "Skill Firing State", Category = "State")
	ESkillFiringState m_eSkillFiringState;

	void ChangeFiringState(ESkillFiringState NextState);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
	
};
