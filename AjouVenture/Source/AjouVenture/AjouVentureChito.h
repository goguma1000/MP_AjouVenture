// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "ChitoAnimInstance.h"
#include "AjouVentureChito.generated.h"

UCLASS()
class AJOUVENTURE_API AAjouVentureChito : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAjouVentureChito();
	virtual void PostInitializeComponents();
	USpringArmComponent* SpringArm;
	UCameraComponent* MainCamera;

	//input actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GreetingAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaulMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInterface*> faces;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//input binding function
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PlayGreeting();
	void Interaction();

	enum class ChitoFace
	{
		Default,
		Smile,
		Angry
	};
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	UChitoAnimInstance* ChitoAnim;
	
	UFUNCTION()
	void GreetingMontageEnded(UAnimMontage* Montage, bool bInterrupeted);
	void ChangeFace(ChitoFace face);
};
