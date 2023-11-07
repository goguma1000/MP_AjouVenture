// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ChitoAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AJOUVENTURE_API UChitoAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UChitoAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables, Meta = (AllowPrivateAccess = true))
	float CurrentSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Variables, Meta = (AllowPrivateAccess = true))
	bool doGreeting = false;

	void PlayGreetingMontage();

private:
	UAnimMontage* GreetingMontage;
};
