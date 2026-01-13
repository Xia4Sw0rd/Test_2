// Fill out your copyright notice in the Description page of Project Settings.


#include "SUCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
//#include "DrawDebugHelpers.h"

// Sets default values
ASUCharacter::ASUCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Components for the Spring Arm for Camera
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	//Components for Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");


	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	jumping = false; 

	bUseControllerRotationYaw = false;

	//TraceDistance = 2000;

}

// Called when the game starts or when spawned
void ASUCharacter::BeginPlay()
{
	Super::BeginPlay();

	AttackAnimDelay = 2.0f;
	
}


// Called to move forward based on float value
void ASUCharacter::MoveForward(float Value) 
{
	//Called to rotate control when moving forward
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	//Adding moving input based on control rotation
	AddMovementInput(ControlRot.Vector(), Value);
}

void ASUCharacter::MoveRight(float Value) 
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red Arrow)
	// Y = Right (Green Arrow)
	// Z = Up (Blue Arrow)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);

}

void ASUCharacter::CheckJump() 
{
	if (jumping) 
	{
		jumping = false;
	}
	else {
		jumping = true;
	}
}



void ASUCharacter::SuperAbility() {


	PlayAnimMontage(AttackAnimIII);

	GetWorldTimerManager().SetTimer(TimerHandle_Super, this, &ASUCharacter::SuperAbility_TimeElapsed, 0.2f);
}

void ASUCharacter::SuperAbility_TimeElapsed() {

	SpawnProjectile(ProjectileClass);
}



void ASUCharacter::PrimaryAttack() {

	
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASUCharacter::PrimaryAttack_TimeElapsed,0.2f);
	
	
}

void ASUCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
//	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

//	FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	SpawnParams.Instigator = this;


//	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

}



void ASUCharacter::AltAttack() {

	PlayAnimMontage(AttackAnimII);

	GetWorldTimerManager().SetTimer(TimerHandle_AltAttack, this, &ASUCharacter::AltAttack_TimeElapsed, 0.2f);

}

void ASUCharacter::AltAttack_TimeElapsed() {

	SpawnProjectile(ProjectileClassII);
}


void ASUCharacter::TeleportAttack() {

	PlayAnimMontage(AttackAnimIV);

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportAttack, this, &ASUCharacter::TeleportAttack, 0.2f);
}

void ASUCharacter::TeleportAttack_TimeElapsed() {

	SpawnProjectile(ProjectileClass);


}


void ASUCharacter::PrimaryInteract()
{
	if (InteractionComp) {

		InteractionComp->PrimaryInteract();

	}
	

}




//void ASUCharacter::TraceForward_Implementation()
//{
//	FVector loc;
//	FRotator Rot;
//	FHitResult Hit;

//	GetController()->GetPlayerViewPoint(loc, Rot);

//	FVector Start = loc;
//	FVector End = Start + (Rot.Vector() * TraceDistance);
//	FCollisionQueryParams TraceParams;
//	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
//}



void ASUCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.0f && Delta < 0.0f) {

		APlayerController * PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}

	if (Delta < 0.0f) {

		GetMesh()->SetScalarParameterValueOnMaterials(TimetoHitParamName, GetWorld()->TimeSeconds);
		
	}
}

// Called every frame
void ASUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping) {

		Jump();

	}

}

// Called to bind functionality to input
void ASUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASUCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASUCharacter::MoveRight);
	

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//InputComponent->BindAction("Jump", IE_Pressed, this, &ASUCharacter::CheckJump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASUCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("AltAttack", IE_Pressed, this, &ASUCharacter::AltAttack);
	PlayerInputComponent->BindAction("Super", IE_Pressed, this, &ASUCharacter::SuperAbility);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &ASUCharacter::TeleportAttack);
	

    PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ASUCharacter::CheckJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASUCharacter::CheckJump);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASUCharacter::PrimaryInteract);

}



void ASUCharacter::SpawnProjectile(TSubclassOf<AActor>ClasstoSpawn) 
{
	if (ensureAlways(ClasstoSpawn)) {
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;		

		FHitResult Hit;
		
		FVector TraceStart = CameraComp->GetComponentLocation();

		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);
		
		//Ignore player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);


		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);


		FRotator ProjRotation;


		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params)) 
		{
			TraceEnd = Hit.ImpactPoint;

			ProjRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint- HandLocation).Rotator();

		}
		else
		{

			ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();


		}

	//	FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClasstoSpawn, SpawnTM, SpawnParams);
	}

    FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);

}

void ASUCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASUCharacter::OnHealthChanged);
}

FVector ASUCharacter::GetPawnViewLocation() const
{



	return CameraComp->GetComponentLocation();



	//return FVector();
}
