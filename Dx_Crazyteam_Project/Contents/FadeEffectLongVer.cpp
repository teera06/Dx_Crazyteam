#include "PreCompile.h"
#include "FadeEffectLongVer.h"

FadeEffectLongVer::FadeEffectLongVer()
{
}

FadeEffectLongVer::~FadeEffectLongVer()
{
}

void FadeEffectLongVer::Init()
{
	SetMaterial("FadeShader_LongVer");

	CopyTarget = UEngineRenderTarget::Create();

	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, Scale, float4::Zero);
}

void FadeEffectLongVer::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();

	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");

	Render(0.0f);

}

void FadeEffectLongVer::EffectON()
{
	Active(true);
}

void FadeEffectLongVer::EffectOff()
{
	Active(false);
}

void FadeEffectLongVer::SetEffect(bool _Triger)
{
	Active(_Triger);
}