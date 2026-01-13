// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SBTTask_SelfHeal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "SAttributeComponent.h"



EBTNodeResult::Type USBTTask_SelfHeal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* MyPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyPawn == nullptr)
	{

		return EBTNodeResult::Failed;





	}
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(MyPawn);
	if (ensure(AttributeComp)) 
	{

		//errors going on MyPawn and AttributeComp on line 28. Going to comment this until I figure out a solution.
		AttributeComp->ApplyHealthChange(MyPawn, AttributeComp->GetHealthMax());
	

	}

	return EBTNodeResult::Succeeded;
}
