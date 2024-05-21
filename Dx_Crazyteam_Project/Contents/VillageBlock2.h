#pragma once
#include "Block.h"
#include "BreakObject.h"

// Ό³Έν :
class AVillageBlock2 : public ABlock, public UBreakObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	AVillageBlock2();
	~AVillageBlock2();

	// delete Function
	AVillageBlock2(const AVillageBlock2& _Other) = delete;
	AVillageBlock2(AVillageBlock2&& _Other) noexcept = delete;
	AVillageBlock2& operator=(const AVillageBlock2& _Other) = delete;
	AVillageBlock2& operator=(AVillageBlock2&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

