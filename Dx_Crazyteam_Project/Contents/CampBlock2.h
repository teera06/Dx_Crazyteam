#pragma once
#include "Block.h"
#include "BreakObject.h"
// Ό³Έν :
class ACampBlock2 : public ABlock, public UBreakObject
{
public:
	// constructor destructor
	ACampBlock2();
	~ACampBlock2();

	// delete Function
	ACampBlock2(const ACampBlock2& _Other) = delete;
	ACampBlock2(ACampBlock2&& _Other) noexcept = delete;
	ACampBlock2& operator=(const ACampBlock2& _Other) = delete;
	ACampBlock2& operator=(ACampBlock2&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

