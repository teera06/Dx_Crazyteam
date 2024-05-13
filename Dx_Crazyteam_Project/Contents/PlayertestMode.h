#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

#include "Player.h"

class APlayertestMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	APlayertestMode(); // 디폴트 생성자
	~APlayertestMode(); // 디폴트 소멸자

	// delete Function
	APlayertestMode(const APlayertestMode& _Other) = delete; // 디폴트 복사 생성자
	APlayertestMode(APlayertestMode&& _Other) noexcept = delete; 
	APlayertestMode& operator=(const APlayertestMode& _Other) = delete; // 디폴트 대입 연산자
	APlayertestMode& operator=(APlayertestMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);
private:
	std::shared_ptr<APlayer> Player1 = nullptr;
};

