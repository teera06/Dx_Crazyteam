#pragma once
#include "CAObject.h"

class APlayer_Shadow : public ACAObject
{
	GENERATED_BODY(ACAObject)

public : 
	APlayer_Shadow();
	~APlayer_Shadow();

	APlayer_Shadow(const APlayer_Shadow& _Other)				 = delete;
	APlayer_Shadow(APlayer_Shadow& _Other) noexcept				 = delete;
	APlayer_Shadow& operator =(const APlayer_Shadow& _Other)	 = delete;
	APlayer_Shadow& operator =(APlayer_Shadow& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

