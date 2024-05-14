#pragma once
#include "Block.h"

// Ό³Έν :
class ACampBlock : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ACampBlock();
	~ACampBlock();

	// delete Function
	ACampBlock(const ACampBlock& _Other) = delete;
	ACampBlock(ACampBlock&& _Other) noexcept = delete;
	ACampBlock& operator=(const ACampBlock& _Other) = delete;
	ACampBlock& operator=(ACampBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private: 

};

