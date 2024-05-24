#pragma once
#include "CAGameMode.h"

class FadeEffectLongVer;
class UImage;
class AEndingGameMode : public ACAGameMode
{
	GENERATED_BODY(ACAGameMode)
public:
	AEndingGameMode();
	~AEndingGameMode();

	AEndingGameMode(const AEndingGameMode& _Other) = delete;
	AEndingGameMode(AEndingGameMode&& _Other) noexcept = delete;
	AEndingGameMode& operator=(const AEndingGameMode& _Other) = delete;
	AEndingGameMode& operator=(AEndingGameMode&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _DeltaTime) override;
	void LevelEnd(ULevel* _DeltaTime) override;

private:
	UImage* Img = nullptr;
	std::shared_ptr<FadeEffectLongVer> BlackFade = nullptr;
};

