#include "PreCompile.h"
#include "FadeEffect.h"

FadeEffect::FadeEffect()
{
}

FadeEffect::~FadeEffect()
{
}

void FadeEffect::Init()
{
	SetMaterial("FadeShader_Black");

	CopyTarget = UEngineRenderTarget::Create();

	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, Scale, float4::Zero);
}

void FadeEffect::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();

	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");

	Render(0.0f);

}

void FadeEffect::EffectON()
{
	Active(true);
}

void FadeEffect::EffectOff()
{
	Active(false);
}

void FadeEffect::SetEffect(bool _Triger)
{
	Active(_Triger);
}