// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "SGameModeBase.h"



static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component"), ECVF_Cheat);



// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	//change HealthMax to float value
	HealthMax = 100;
	Health = HealthMax;


	Credits = 0;
	Credits = CreditMax;
	
}



bool USAttributeComponent::isAlive()const
{
	return Health > 0.0f;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

bool USAttributeComponent::IsFullWallet() const {

	return Credits == CreditMax;

}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

float USAttributeComponent::GetHealth() const
{

	return Health;


}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::Kill(AActor*InstigatorActor)
{

	return ApplyHealthChange(InstigatorActor, -GetHealthMax());


}



//float USAttributeComponent::HealthRecovery() const
//{
	//return;
//}



bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged()&& Delta < 0.0f) {




		return false;



	}
	
	if (Delta < 0.0f) 
	{

		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;



	}
	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	float Healthrecovery = FMath::Clamp(Delta, 0.0f, HealthMax);

	float ActualDelta = NewHealth - OldHealth;
	// Had to lowercase delta to prevent errors. May also comment this if this method remains unsuccessful.
	float Actualdelta = Healthrecovery + OldHealth;
	
	Health += Delta;


	OnHealthChanged.Broadcast(InstigatorActor,this, Health, Delta);


	// Died
	if (ActualDelta < 0.0f && Health == 0.0f)

	{
		ASGameModeBase* GM = (GetWorld()->GetAuthGameMode<ASGameModeBase>());

		if (GM) 
		
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}


	}

	return ActualDelta != 0;


}

bool USAttributeComponent::ApplyCreditChange(AActor* InstigatorActor, float Delta)
{

	float OldCredit = Credits;
	float NewCredit = FMath::Clamp(Credits + Delta, 0.0f, CreditMax);
	float ActualDelta = NewCredit + OldCredit;

	return ActualDelta != 0;


	OnHealthChanged.Broadcast(InstigatorActor, this, Credits, Delta);
}

//float USAttributeComponent::DamageAmount() const
//{
	//return;
//}


