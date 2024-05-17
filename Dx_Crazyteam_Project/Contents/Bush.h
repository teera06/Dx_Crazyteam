#pragma once
#include "Block.h"
#include "BreakObject.h"

// Ό³Έν :
class ABlock;
class ABush : public ABlock, public UBreakObject
{
	GENERATED_BODY(ABlock)
public:
	// constructor destructor
	ABush();
	~ABush();

	// delete Function
	ABush(const ABush& _Other) = delete;
	ABush(ABush&& _Other) noexcept = delete;
	ABush& operator=(const ABush& _Other) = delete;
	ABush& operator=(ABush&& _Other) noexcept = delete;

	void SetPossessBlock(std::shared_ptr<AMapObject> _Block);

	std::shared_ptr<AMapObject> GetPossessBlock()
	{
		return PossessBlock;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::shared_ptr<AMapObject> PossessBlock = nullptr;
private:

};

