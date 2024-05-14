#pragma once
#include "CAGameMode.h"

class UMapDebugGUI;
class ATestGameMode : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)
public:
	// constrcuter destructer
	ATestGameMode(); // 디폴트 생성자
	~ATestGameMode(); // 디폴트 소멸자

	// delete Function
	ATestGameMode(const ATestGameMode& _Other) = delete; // 디폴트 복사 생성자
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete; 
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete; // 디폴트 대입 연산자
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	std::shared_ptr<UMapDebugGUI> MapDebugWindow;
	std::shared_ptr<APlayer> Player1 = nullptr;
};

