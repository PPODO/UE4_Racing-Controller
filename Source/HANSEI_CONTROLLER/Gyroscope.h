#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gyroscope.generated.h"

USTRUCT()
struct FInputMotionData {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Motion")
		FVector Tilt;
	UPROPERTY(EditAnywhere, Category = "Motion")
		FVector RotationRate;
	UPROPERTY(EditAnywhere, Category = "Motion")
		FVector Gravity;
	UPROPERTY(EditAnywhere, Category = "Motion")
		FVector Acceleration;

	FInputMotionData() {};
	FInputMotionData(FVector& _Tilt, FVector& _RotationRate, FVector& _Gravity, FVector& _Acceleration) : Tilt(_Tilt), RotationRate(_RotationRate), Gravity(_Gravity), Acceleration(_Acceleration) {};
};

FORCEINLINE FArchive& operator<<(FArchive& Ar, FInputMotionData& Data) {
	Ar << Data.Tilt;
	Ar << Data.RotationRate;
	Ar << Data.Gravity;
	Ar << Data.Acceleration;
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


};