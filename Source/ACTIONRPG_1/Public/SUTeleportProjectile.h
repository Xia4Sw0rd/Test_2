// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SUTeleportProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;





UCLASS()
class ACTIONRPG_1_API ASUTeleportProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASUTeleportProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	


	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp;


//	UPROPERTY(EditDefaultsOnly, Category = "Teleport");
//	float TeleportDelay;

//	UPROPERTY(EditDefaultsOnly, Category = "Teleport");
//	float DetonateDelay;

	//FTimerHandle TimerHandle_DelayDetonate;


	//virtual void Explode_Implementation() override;

	//void Explode();

	//void ImpactVFX();

	//void Explode_Implementation();

//	virtual void Explode_Implementation() override;

	//void ImpactVFX();

	

	//void TeleportInstigator();
	



public:	
	
	virtual void Tick(float DeltaTime) override;
	//ASUTeleportProjectile();

};
