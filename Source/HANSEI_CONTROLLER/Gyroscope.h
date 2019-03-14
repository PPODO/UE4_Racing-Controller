#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HANSEI_CONTROLLERGameModeBase.h"
#include "Gyroscope.generated.h"

FORCEINLINE FArchive& operator<<(FArchive& Ar, FInputMotionData& Data) {
	Ar << Data.Gravity;
	Ar << Data.bIsPressedHandBreak;
	Ar << Data.bIsPressedAcc;
	return Ar;
}

UCLASS()
class HANSEI_CONTROLLER_API AGyroscope : public AActor
{
	GENERATED_BODY()

public:
	AGyroscope();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	class APlayerController* m_PlayerController;
	class AHANSEI_CONTROLLERGameModeBase* m_GameMode;

	FVector Tilt, RotationRate, Gravity, Acceleration;

public:
	float CX, CY;

};