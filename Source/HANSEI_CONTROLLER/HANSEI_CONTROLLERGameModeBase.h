#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HANSEI_CONTROLLERGameModeBase.generated.h"

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
	
public:
	UPROPERTY(BlueprintReadOnly)
		bool bIsConnected;

public:
	UFUNCTION(BlueprintCallable)
		void StartSender(const FString& IP);

	FORCEINLINE SOCKETSender* GetSenderSocket() const { return m_Sender; }

};