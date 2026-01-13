// Fill out your copyright notice in the Description page of Project Settings.


#include "SUMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SUGameplayFunctionLibrary.h"
//#include "SExplosiveBarrel.cpp"


// Sets default values
ASUMagicProjectile::ASUMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASUMagicProjectile::OnActorOverlap);
	//SphereComp->SetCollisionResponseToAllChannels(ECC_Pawn,ECR_Overlap);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 8000;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

	//Both Impacts remain to be undefined. Need to sort this out at a later date
	//ImpactShakeInnerRadius = 0.0f;
	//ImpactShakeOuterRadius = 1500.0f;


	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
	
	float Damageamount = 20.0f;
}

void ASUMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator()) 
	{

		USAttributeComponent*AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp) {
			//When you get back, work on this part. You got this!
			
			// minus in front of DamageAmount to apply the change as damage, not healing
			AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount);

			// Only explode when we hit something valid
			//Explode();
		}



		if(USUGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
		
		//	Explode();
		
		}
	}


}



//void ASUMagicProjectile::Explode()
//{
	
	

	


//}

// Called when the game starts or when spawned
void ASUMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASUMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

