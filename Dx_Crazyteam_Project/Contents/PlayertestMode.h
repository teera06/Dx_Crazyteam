#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>


#include "Village.h"
#include "Player.h"

class APlayerTestMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	APlayerTestMode(); // 디폴트 생성자
	~APlayerTestMode(); // 디폴트 소멸자

	// delete Function
	APlayerTestMode(const APlayerTestMode& _Other) = delete; // 디폴트 복사 생성자
	APlayerTestMode(APlayerTestMode&& _Other) noexcept = delete; 
	APlayerTestMode& operator=(const APlayerTestMode& _Other) = delete; // 디폴트 대입 연산자
	APlayerTestMode& operator=(APlayerTestMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel);
	void LevelEnd(ULevel* _NextLevel);
private:
	std::shared_ptr<AVillage> Village = nullptr;
	std::shared_ptr<APlayer> Player1 = nullptr;
};

