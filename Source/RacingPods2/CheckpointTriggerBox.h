// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckpointTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class RACINGPODS2_API ACheckpointTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(Category = Race, EditAnywhere, BlueprintReadOnly)
		bool lastCheckpoint;

public:

	ACheckpointTriggerBox();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
};
