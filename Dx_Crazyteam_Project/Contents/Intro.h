#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/EngineNetWindow.h>

class AServerGameMode;
class AUitestMonde;
class UImage;
class AIntro : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)


public:
	// constrcuter destructer
	AIntro();
	~AIntro();

	// delete Function
	AIntro(const AIntro& _Other) = delete;
	AIntro(AIntro&& _Other) noexcept = delete;
	AIntro& operator=(const AIntro& _Other) = delete;
	AIntro& operator=(AIntro&& _Other) noexcept = delete;

	void SetFunction(std::function<void()> _Function)
	{
		Function = _Function;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* IntroUI = nullptr;
	UImage* StartUI = nullptr;
	UImage* TextInputUI = nullptr;
	UImage* GameStartButton = nullptr;

	std::function<void()> Function = nullptr;
	AServerGameMode* ServerGameMode = nullptr;
};

