// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointTriggerBox.h"
#include "VehiclePawn.h"
#include "DrawDebugHelpers.h"


ACheckpointTriggerBox::ACheckpointTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ACheckpointTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACheckpointTriggerBox::OnOverlapEnd);
}

void ACheckpointTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void ACheckpointTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (AVehiclePawn* Vehicle = Cast<AVehiclePawn>(OtherActor))
	{
		if (lastCheckpoint)
		{
			Vehicle->increaseLap();
		}
		Vehicle->setRespawnLocation(this->GetActorLocation());
	}
}

void ACheckpointTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
