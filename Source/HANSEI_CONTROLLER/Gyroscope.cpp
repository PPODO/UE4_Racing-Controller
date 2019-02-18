#include "Gyroscope.h"
#include "SOCKETSender.h"
#include "HANSEI_CONTROLLERGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Components/InputComponent.h"

AGyroscope::AGyroscope() {
	m_GameMode = nullptr;

	PrimaryActorTick.bCanEverTick = true;
}

void AGyroscope::BeginPlay() {
	Super::BeginPlay();

	if ((m_GameMode = Cast<AHANSEI_CONTROLLERGameModeBase>(GetWorld()->GetAuthGameMode())) == nullptr || (m_PlayerController = GetWorld()->GetFirstPlayerController()) == nullptr) {
		m_GameMode = Cast<AHANSEI_CONTROLLERGameModeBase>(GetWorld()->GetAuthGameMode());
		m_PlayerController = GetWorld()->GetFirstPlayerController()->InputComponent;
	}
}

void AGyroscope::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (m_GameMode && m_PlayerController) {
		m_PlayerController->GetInputMotionState(Tilt, RotationRate, Gravity, Acceleration);

		Tilt = FVector::RadiansToDegrees(Tilt);
		RotationRate = FVector::RadiansToDegrees(RotationRate);
		Acceleration = FVector::RadiansToDegrees(Acceleration);

		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Black, Acceleration.ToString());
		GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Green, Gravity.ToString());
		GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Blue, RotationRate.ToString());
		GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Red, Tilt.ToString());

		if (m_GameMode->GetSenderSocket() && m_GameMode->bIsConnected) {
			FInputMotionData Data(Tilt, RotationRate, Gravity, Acceleration);
			m_GameMode->GetSenderSocket()->SendTo(Data);
		}
	}
}