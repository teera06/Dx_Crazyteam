#pragma once
#include <EngineCore/EngineRenderTarget.h>

class FadeEffect : public UEffect
{
public:
	FadeEffect();
	~FadeEffect();

	FadeEffect(const FadeEffect& _Other) = delete;
	FadeEffect(FadeEffect&& _Other) noexcept = delete;
	FadeEffect& operator=(const FadeEffect& _Other) = delete;
	FadeEffect& operator=(FadeEffect&& _Other) noexcept = delete;
	void EffectON();
	void EffectOff();
	void SetEffect(bool _Triger);

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;


private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;
};

