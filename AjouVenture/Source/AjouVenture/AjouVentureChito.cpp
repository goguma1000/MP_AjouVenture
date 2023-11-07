// Fill out your copyright notice in the Description page of Project Settings.


#include "AjouVentureChito.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AAjouVentureChito::AAjouVentureChito()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	//Create SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true; //Rotate the arm based on the controller

	//Create Camera
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MAINCAMERA"));
	MainCamera->SetupAttachment(SpringArm);
	MainCamera->bUsePawnControlRotation = false;

	static ConstructorHelpers::FClassFinder<UAnimInstance> CHITO_ANIM(TEXT("/Game/2023_Character1027/Chito/ABP_Chito.ABP_Chito_C"));
	if (CHITO_ANIM.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(CHITO_ANIM.Class);
	}

}

void AAjouVentureChito::PostInitializeComponents() {
	Super::PostInitializeComponents();
	ChitoAnim = Cast<UChitoAnimInstance>(GetMesh()->GetAnimInstance());
	if (ChitoAnim != nullptr) {
		ChitoAnim->OnMontageEnded.AddDynamic(this, &AAjouVentureChito::GreetingMontageEnded);
	}
}

// Called when the game starts or when spawned
void AAjouVentureChito::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer( ))) {
			Subsystem->AddMappingContext(DefaulMappingContext, 0);
		}
	}
}

// Called every frame
void AAjouVentureChito::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAjouVentureChito::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAjouVentureChito::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAjouVentureChito::Look);
		EnhancedInputComponent->BindAction(GreetingAction, ETriggerEvent::Started, this, &AAjouVentureChito::PlayGreeting);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AAjouVentureChito::Interaction);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhacned Input component!"), *GetNameSafe(this));
	}
}

void AAjouVentureChito::Move(const FInputActionValue& Value) {
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAjouVentureChito::Look(const FInputActionValue& Value) {
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAjouVentureChito::PlayGreeting() {
	ChangeFace(ChitoFace::Smile);
	ChitoAnim->PlayGreetingMontage();
}

void AAjouVentureChito::Interaction() {
	/*int range = 100;
	FHitResult result;
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;
	Params.AddIgnoredActor(GetOwner());
	FVector start = GetActorLocation();
	FVector end = start + GetActorForwardVector() * range;
	bool bResult = GetWorld()->LineTraceSingleByChannel(result,start, end, ECC_GameTraceChannel1,Params);
	DrawDebugLine(GetWorld(), start, end, FColor::Red,false, 2.0f);
	if (bResult) {
		 UClass* inter = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/Blueprints/BP_Interface/InteractableActor.InteractableActor_C"), nullptr,LOAD_None,nullptr);
		if (inter == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("class not found"));
		}
		if (result.GetActor()->GetClass()->ImplementsInterface(inter)) {

		}
	}
	*/
}

void AAjouVentureChito::GreetingMontageEnded(UAnimMontage* Montage, bool bInterrupeted) {
	ChangeFace(ChitoFace::Default);
}
void AAjouVentureChito::ChangeFace(ChitoFace face) {
	switch (face)
	{
	case ChitoFace::Default:
		GetMesh()->SetMaterial(0, faces[0]);
		break;
	case ChitoFace::Smile:
		GetMesh()->SetMaterial(0, faces[1]);
		break;
	case ChitoFace::Angry:
		break;
	default:
		break;
	}
}