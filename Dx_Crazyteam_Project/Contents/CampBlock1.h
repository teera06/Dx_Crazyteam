#pragma once
#include "Block.h"
#include "BreakObject.h"

// Ό³Έν :
class ACampBlock1 : public ABlock, public UBreakObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ACampBlock1();
	~ACampBlock1();

	// delete Function
	ACampBlock1(const ACampBlock1& _Other) = delete;
	ACampBlock1(ACampBlock1&& _Other) noexcept = delete;
	ACampBlock1& operator=(const ACampBlock1& _Other) = delete;
	ACampBlock1& operator=(ACampBlock1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private: 

};

