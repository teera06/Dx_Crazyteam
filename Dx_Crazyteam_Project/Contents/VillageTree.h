#pragma once
#include "Block.h"

// Ό³Έν :
class AVillageTree : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	AVillageTree();
	~AVillageTree();

	// delete Function
	AVillageTree(const AVillageTree& _Other) = delete;
	AVillageTree(AVillageTree&& _Other) noexcept = delete;
	AVillageTree& operator=(const AVillageTree& _Other) = delete;
	AVillageTree& operator=(AVillageTree&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

