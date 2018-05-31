// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KSkill.generated.h"

UENUM(BlueprintType)
enum class ESkillFiringState : uint8
{
	Idle,
	Firing,
};

/**
 * 
 */
UCLASS(Blueprintable)
class KGAME_API UKSkill : public UObject
{
	GENERATED_BODY()

public:
	/** Called after we enter the firing state. */
	UFUNCTION(BlueprintNativeEvent, Category = "Firing")
	void StartFiringState();
	/** Pre fire logic. */
	UFUNCTION(BlueprintNativeEvent, Category = "Firing")
	void PreFire();
	/** Pre fire logic that occurs after the delay. */
	UFUNCTION(BlueprintNativeEvent, Category = "Firing")
	void DelayedPreFire();
	/** Officially Fire. */
	UFUNCTION(BlueprintNativeEvent, Category = "Firing")
	void Fire();
	/** Post fire logic. */
	UFUNCTION(BlueprintNativeEvent, Category = "Firing")
	void PostFire();
	/** Post fire logic that occurs after the delay. */
	UFUNCTION(BlueprintNativeEvent, Category = "Firing")
	void DelayedPostFire();
	/** Called before leave the firing state. */
	UFUNCTION(BlueprintNativeEvent, Category = "Firing")
	void EndFiringState();
	
	/** Returns our Skill State. */
	UFUNCTION(BlueprintPure, Category = "State")
	virtual ESkillFiringState GetSkillState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	ESkillFiringState eSkillState;

};
