// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "SUCharacter.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("su.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);



ASGameModeBase::ASGameModeBase()
{

	SpawnTimerInterval = 2.0f;


}

void ASGameModeBase::StartPlay()
{

	Super::StartPlay();

	//Continous timer to spawn more bots
	//// Actual amount of bots and whether its allowed to spawn determined by spawn logic later in the chain...
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ASGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);


}






void ASGameModeBase::SpawnBotTimerElapsed()
{

	if(!CVarSpawnBots.GetValueOnGameThread())
	
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar 'CVarSpawnBots'"));
		return;
	}



	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{

		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ASGameModeBase::OnQueryCompleted);

	}

}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{

	if(QueryStatus != EEnvQueryStatus::Success)
	{
	
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query failed!"));
		return;
	
	}
	
	
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
	
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
	}
}
void ASGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller)) 
	{

		Controller->UnPossess();
		RestartPlayer(Controller);

	}


}
void ASGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{

	ASUCharacter* Player = Cast <ASUCharacter>(VictimActor);

	if (Player)

	{

		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());


		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay,Delegate, RespawnDelay, false);



	}
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victims %s, Killer %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
}