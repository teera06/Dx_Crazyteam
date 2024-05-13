#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>

class AtestGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AtestGameMode(); // 디폴트 생성자
	~AtestGameMode(); // 디폴트 소멸자

	// delete Function
	AtestGameMode(const AtestGameMode& _Other) = delete; // 디폴트 복사 생성자
	AtestGameMode(AtestGameMode&& _Other) noexcept = delete; 
	AtestGameMode& operator=(const AtestGameMode& _Other) = delete; // 디폴트 대입 연산자
	AtestGameMode& operator=(AtestGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);
private:
};

