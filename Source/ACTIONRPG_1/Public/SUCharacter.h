// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SUCharacter.generated.h"




class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class USAttributeComponent;
class UAniMontage;

UCLASS()
class ACTIONRPG_1_API ASUCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor>ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "AltAttack")
	TSubclassOf<AActor>ProjectileClassII;

	UPROPERTY(EditAnywhere, Category = "Super")
	TSubclassOf<AActor>ProjectileClassIII;

	UPROPERTY(EditAnywhere,Category = "Teleport")
	TSubclassOf<AActor>ProjectileClassIV;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere, Category = "AltAttack")
	UAnimMontage* AttackAnimII;

	UPROPERTY(EditAnywhere, Category = "Super")
	UAnimMontage* AttackAnimIII;

	UPROPERTY(EditAnywhere, Category = "Teleport")
	UAnimMontage* AttackAnimIV;

	UPROPERTY(EditDefaultsOnly,Category = "Attack")
	float AttackAnimDelay;




	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_AltAttack;
	FTimerHandle TimerHandle_Super;
	FTimerHandle TimerHandle_TeleportAttack;
	
	
	



public:
	// Sets default values for this character's properties
	ASUCharacter();

protected:


	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComp;

	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* AudioComp;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimetoHitParamName;


	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void MoveForward(float Value);
	void MoveRight(float value);
	//void Jump (float value);
	void PrimaryAttack();
    void PrimaryAttack_TimeElapsed();

	void AltAttack();
	void AltAttack_TimeElapsed();

	void SuperAbility();
	void SuperAbility_TimeElapsed();

	void PrimaryInteract();

	void TeleportAttack();
	void TeleportAttack_TimeElapsed();

	void SpawnProjectile();



	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpawnProjectile(TSubclassOf<AActor> ClasstoSpawn);

	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;

private:
	void CheckJump();

	UPROPERTY();
	bool jumping;








};


