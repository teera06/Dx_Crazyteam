#pragma once
#include "Block.h"

// Ό³Έν :
class RedHouse : public ABlock
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	RedHouse();
	~RedHouse();

	// delete Function
	RedHouse(const RedHouse& _Other) = delete;
	RedHouse(RedHouse&& _Other) noexcept = delete;
	RedHouse& operator=(const RedHouse& _Other) = delete;
	RedHouse& operator=(RedHouse&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

