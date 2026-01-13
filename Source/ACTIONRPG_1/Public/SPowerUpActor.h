// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USAttributeComponent;
class UPrimitiveComponent;





UCLASS()
class ACTIONRPG_1_API ASPowerUpActor : public AActor
{
	GENERATED_BODY()




protected:


	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Attributes")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	float HealthRecovery;




	virtual void BeginPlay() override;

public:


	virtual void Tick(float DeltaTime) override;

	ASPowerUpActor();
};
