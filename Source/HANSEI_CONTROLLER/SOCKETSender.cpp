#include "SOCKETSender.h"
#include "Gyroscope.h"
#include "SocketSubsystem.h"
#include "UdpSocketBuilder.h"
#include "ArrayWriter.h"
#include "Engine/Engine.h"

bool SOCKETSender::StartUDPSender(const FString & SocketName, const FString & IP) {
	bool Valid = false;

	m_Address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	if (m_Address) {
		m_Address->SetIp(*IP, Valid);
		m_Address->SetPort(3500);
	}

	if (!Valid) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Invalid IP!!");
		}
		return false;
	}

	m_Socket = FUdpSocketBuilder(*SocketName).AsReusable().WithBroadcast();
	if (!m_Socket) {
		return false;
	}
	int32 NewSize = 1024;
	m_Socket->SetSendBufferSize(NewSize, NewSize);
	m_Socket->SetReceiveBufferSize(NewSize, NewSize);

	return true;
}

bool SOCKETSender::SendTo(FInputMotionData& Data) {
	FArrayWriter Writer;
	int32 SendBytes = 0;

	Writer << Data;

	if (m_Socket) {
		m_Socket->SendTo(Writer.GetData(), Writer.Num(), SendBytes, *m_Address);
	}
	if (SendBytes <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Send Error!"));
		return false;
	}
	return true;
}

SOCKETSender::~SOCKETSender() {
	if (m_Socket) {
		m_Socket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(m_Socket);
	}
}