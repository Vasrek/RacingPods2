// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementcomponent4W.h"

AVehiclePawn::AVehiclePawn()
{
	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	// Adjust the tire
	Vehicle4W->MinNormalizedTireLoad = MinTireLoad;
	Vehicle4W->MinNormalizedTireLoadFiltered = MinTireLoadFiltered;
	Vehicle4W->MaxNormalizedTireLoad = MaxTireLoad;
	Vehicle4W->MaxNormalizedTireLoadFiltered = MaxTireLoadFiltered;

	// Torque setup
	Vehicle4W->MaxEngineRPM = MaxEngineRPM;
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(FirstTorqueMin, FirstTorqueMax);
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(SecondTorqueMin, SecondTorqueMax);
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(ThirdTorqueMin, ThirdTorqueMax);

	// Adjust the steering 
	Vehicle4W->SteeringCurve.GetRichCurve()->Reset();
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(FirstSteeringMin, FirstSteeringMax);
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(SecondSteeringMin, SecondSteeringMax);
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(ThirdSteeringMin, ThirdSteeringMax);

	Vehicle4W->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_4W;
	Vehicle4W->DifferentialSetup.FrontRearSplit = 0.65f;

	// Automatic gearbox
	Vehicle4W->TransmissionSetup.bUseGearAutoBox = GearAutoBox;
	Vehicle4W->TransmissionSetup.GearSwitchTime = GearSwitchTime;
	Vehicle4W->TransmissionSetup.GearAutoBoxLatency = GearAutoBoxLatency;

	// Spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bUsePawnControlRotation = true;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->FieldOfView = 90.0f;

}

void AVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Throttle", this, &AVehiclePawn::ApplyThrottle);
	PlayerInputComponent->BindAxis("Steer", this, &AVehiclePawn::ApplySteering);
	PlayerInputComponent->BindAxis("LookUp", this, &AVehiclePawn::Lookup);
	PlayerInputComponent->BindAxis("Turn", this, &AVehiclePawn::Turn);

	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AVehiclePawn::OnHandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AVehiclePawn::OnHandbrakeReleased);
}

void AVehiclePawn::ApplyThrottle(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void AVehiclePawn::ApplySteering(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void AVehiclePawn::Lookup(float Val)
{
	if (Val != 0.f)
	{
		AddControllerPitchInput(Val);
	}
}

void AVehiclePawn::Turn(float Val)
{
	if (Val != 0.f)
	{
		AddControllerYawInput(Val);
	}
}

void AVehiclePawn::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AVehiclePawn::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}
