#pragma once
#include "Block.h"
#include "BreakObject.h"

// Ό³Έν :
class AVillageBlock1 : public ABlock, public UBreakObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	AVillageBlock1();
	~AVillageBlock1();

	// delete Function
	AVillageBlock1(const AVillageBlock1& _Other) = delete;
	AVillageBlock1(AVillageBlock1&& _Other) noexcept = delete;
	AVillageBlock1& operator=(const AVillageBlock1& _Other) = delete;
	AVillageBlock1& operator=(AVillageBlock1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

