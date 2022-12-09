// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathTriggerBox.h"
#include "VehiclePawn.h"
#include "DrawDebugHelpers.h"

ADeathTriggerBox::ADeathTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ADeathTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ADeathTriggerBox::OnOverlapEnd);
}

void ADeathTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void ADeathTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (AVehiclePawn* Vehicle = Cast<AVehiclePawn>(OtherActor))
	{
		Vehicle->SetActorRotation(FRotator::ZeroRotator);
		Vehicle->SetActorLocation(Vehicle->getRespawnLocation(), false, (FHitResult*)nullptr, ETeleportType::TeleportPhysics);
	}
}

void ADeathTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}
