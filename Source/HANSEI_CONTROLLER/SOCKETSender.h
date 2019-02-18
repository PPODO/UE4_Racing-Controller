#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"

struct FInputMotionData;

class HANSEI_CONTROLLER_API SOCKETSender {
private:
	FSocket* m_Socket;
	TSharedPtr<FInternetAddr> m_Address;

	int32 bIsUDP : 1;

public:
	SOCKETSender() : bIsUDP(false), m_Address(nullptr), m_Socket(nullptr) {};

	bool StartUDPSender(const FString& SocketName, const FString& IP);

	bool SendTo(FInputMotionData& Data);

	~SOCKETSender();
};