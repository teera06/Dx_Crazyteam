#pragma once
#include "Block.h"
// Ό³Έν :
class ACampBlock3 : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ACampBlock3();
	~ACampBlock3();

	// delete Function
	ACampBlock3(const ACampBlock3& _Other) = delete;
	ACampBlock3(ACampBlock3&& _Other) noexcept = delete;
	ACampBlock3& operator=(const ACampBlock3& _Other) = delete;
	ACampBlock3& operator=(ACampBlock3&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

