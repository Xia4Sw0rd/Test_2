// Fill out your copyright notice in the Description page of Project Settings.


#include "SUTeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASUTeleportProjectile::ASUTeleportProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionProfileName("Projectile II");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 6000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	

	//TeleportDelay = 0.2f;
	//DetonateDelay = 0.2f;
	

}

// Called when the game starts or when spawned
void ASUTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();


//	GetWorldTimerManager().SetTimer(TimerHandle_DelayDetonate, this, &ASUTeleportProjectile::Explode, DetonateDelay);
	
	
}


//void ASUTeleportProjectile::Explode_Implementation() {

	//GetWorldTimerManager().ClearTimer(TimerHandle_DelayDetonate);


//	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	//EffectComp->DeactivateSystem();


	//MovementComp->StopMovementImmediately();
	//SetActorEnableCollision(false);

	//FTimerHandle TimerHandle_DelayedTeleport;
	//GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ASUTeleportProjectile::TeleportInstigator, TeleportDelay);





//}








//void ASUTeleportProjectile::TeleportInstigator() 
//{
//	AActor* ActorToTeleport = GetInstigator();
//	if(ensure(ActorToTeleport))
//	{
	
//		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	
//	}


//}




// Called every frame
void ASUTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

