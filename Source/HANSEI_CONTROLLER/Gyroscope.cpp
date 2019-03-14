#include "Gyroscope.h"
#include "SOCKETSender.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"

AGyroscope::AGyroscope() {
	m_GameMode = nullptr;
	CY = CX = 0;
	PrimaryActorTick.bCanEverTick = true;
}

void AGyroscope::BeginPlay() {
	Super::BeginPlay();

	if ((m_GameMode = Cast<AHANSEI_CONTROLLERGameModeBase>(GetWorld()->GetAuthGameMode())) == nullptr || (m_PlayerController = GetWorld()->GetFirstPlayerController()) == nullptr) {
		m_GameMode = Cast<AHANSEI_CONTROLLERGameModeBase>(GetWorld()->GetAuthGameMode());
	}
}

void AGyroscope::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	float YY;
	if (m_GameMode && m_PlayerController) {
		m_PlayerController->GetInputMotionState(Tilt, RotationRate, Gravity, Acceleration);

		YY = (FMath::ClampAngle(Gravity.Y, -9.f, 9.f) * 10);

		if (m_GameMode->GetSenderSocket() && m_GameMode->bIsConnected) {
			FInputMotionData Data = m_GameMode->GetMotionData();
			Data.Gravity = Gravity;
			Data.Gravity.Y = FMath::Sin(FMath::DegreesToRadians(YY * m_GameMode->GetValue()));

			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(2, 1.f, FColor::Red, Data.Gravity.ToString());
				GEngine->AddOnScreenDebugMessage(3, 1.f, FColor::Blue, FString::Printf(TEXT("Acc : %d"), Data.bIsPressedAcc));
				GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("Hand : %d"), Data.bIsPressedHandBreak));
			}
			m_GameMode->GetSenderSocket()->SendTo(Data);
		}
	}
}