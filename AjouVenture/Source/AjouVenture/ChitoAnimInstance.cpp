// Fill out your copyright notice in the Description page of Project Settings.


#include "ChitoAnimInstance.h"

UChitoAnimInstance::UChitoAnimInstance() {
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GREETING_MONTAGE(TEXT("/Game/2023_Character1027/Chito/Animations/MTG_Greeting.MTG_Greeting"));
	if (GREETING_MONTAGE.Succeeded()) {
		GreetingMontage = GREETING_MONTAGE.Object;
	}
}

void UChitoAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!IsValid(Pawn)) return;

	CurrentSpeed = Pawn->GetVelocity().Size();
}

void UChitoAnimInstance::PlayGreetingMontage() {
	if (!Montage_IsPlaying(GreetingMontage)) {
		Montage_Play(GreetingMontage);
	}
}