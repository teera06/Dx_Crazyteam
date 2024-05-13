#pragma once
#include "MapObject.h"

// Ό³Έν :
class Block : public AMapObject
{
	GENERATED_BODY(AMapObject)
public:
	// constructor destructor
	Block();
	~Block();

	// delete Function
	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};

