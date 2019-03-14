#include "HANSEI_CONTROLLERGameModeBase.h"
#include "SOCKETSender.h"

AHANSEI_CONTROLLERGameModeBase::AHANSEI_CONTROLLERGameModeBase() {
	bIsConnected = false;

	PrimaryActorTick.bCanEverTick = true;
}

void AHANSEI_CONTROLLERGameModeBase::BeginPlay() {
	Super::BeginPlay();

	m_Sender = new SOCKETSender;
	if (!m_Sender) {
		m_Sender = new SOCKETSender;
	}
}

void AHANSEI_CONTROLLERGameModeBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AHANSEI_CONTROLLERGameModeBase::BeginDestroy() {
	Super::BeginDestroy();

	if (m_Sender) {
		delete m_Sender;
	}
}

void AHANSEI_CONTROLLERGameModeBase::StartSender(const FString& IP) {
	if (m_Sender) {
		bIsConnected = m_Sender->StartUDPSender("Sender Socket", IP);
	}
}

void AHANSEI_CONTROLLERGameModeBase::SetMotionData(bool PressedHand, bool PressedAcc) {
	m_MotionData.bIsPressedHandBreak = PressedHand;
	m_MotionData.bIsPressedAcc = PressedAcc;
}

void AHANSEI_CONTROLLERGameModeBase::SetValue(float f) {
	Value = f;
}