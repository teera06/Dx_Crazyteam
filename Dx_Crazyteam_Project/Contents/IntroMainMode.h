#pragma once
#include <EngineCore/GameMode.h>

class AIntro;
class ATitleMenu;
class UEngineSoundPlayer;

class AIntroMainMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AIntroMainMode(); // 디폴트 생성자
	~AIntroMainMode(); // 디폴트 소멸자

	// delete Function
	AIntroMainMode(const AIntroMainMode& _Other) = delete; // 디폴트 복사 생성자
	AIntroMainMode(AIntroMainMode&& _Other) noexcept = delete; 
	AIntroMainMode& operator=(const AIntroMainMode& _Other) = delete; // 디폴트 대입 연산자
	AIntroMainMode& operator=(AIntroMainMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);
private:
	UEngineSoundPlayer BGM;
	std::shared_ptr<AIntro> Intro = nullptr;
};

