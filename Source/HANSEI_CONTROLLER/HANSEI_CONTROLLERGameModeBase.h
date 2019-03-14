#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HANSEI_CONTROLLERGameModeBase.generated.h"

USTRUCT()
struct FInputMotionData {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Motion")
		FVector Gravity;
	UPROPERTY(EditAnywhere, Category = "Motion")
		bool bIsPressedHandBreak;
	UPROPERTY(EditAnywhere, Category = "Motion")
		bool bIsPressedAcc;

	FInputMotionData() {};
	FInputMotionData(FVector& _Gravity, bool bIsPressedHand, bool IsPressedAcc) : Gravity(_Gravity), bIsPressedHandBreak(bIsPressedHand), bIsPressedAcc(IsPressedAcc) {};
};

UCLASS()
class HANSEI_CONTROLLER_API AHANSEI_CONTROLLERGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AHANSEI_CONTROLLERGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;

private:
	class SOCKETSender* m_Sender;
	float Value;
	FInputMotionData m_MotionData;
	
public:
	UPROPERTY(BlueprintReadOnly)
		bool bIsConnected;

public:
	UFUNCTION(BlueprintCallable)
		void StartSender(const FString& IP);

	FORCEINLINE SOCKETSender* GetSenderSocket() const { return m_Sender; }

public:
	UFUNCTION(BlueprintCallable)
		void SetMotionData(bool PressedHand, bool PressedAcc);

	UFUNCTION(BlueprintCallable)
		void SetValue(float f);

	inline FInputMotionData GetMotionData() const { return m_MotionData; }
	inline float GetValue() const { return Value; }

};