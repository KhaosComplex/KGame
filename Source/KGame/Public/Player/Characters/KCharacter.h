// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KCharacter.generated.h"

// Multicast delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const class AKCharacter*, Character);

UCLASS(config=Game)
class AKCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AKCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

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
	float GetHealthPct() const;

	/** Returns our native on health changed delegate. */
	DECLARE_EVENT_OneParam(AKCharacter, FOnHealthChangedNative, const class AKCharacter*);
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

