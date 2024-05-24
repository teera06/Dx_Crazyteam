#pragma once
#include <EngineCore/EngineRenderTarget.h>

class FadeEffectLongVer : public UEffect
{
public:
	FadeEffectLongVer();
	~FadeEffectLongVer();

	FadeEffectLongVer(const FadeEffectLongVer& _Other) = delete;
	FadeEffectLongVer(FadeEffectLongVer&& _Other) noexcept = delete;
	FadeEffectLongVer& operator=(const FadeEffectLongVer& _Other) = delete;
	FadeEffectLongVer& operator=(FadeEffectLongVer&& _Other) noexcept = delete;
	void EffectON();
	void EffectOff();
	void SetEffect(bool _Triger);

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;


private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;
};

