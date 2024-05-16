#pragma once
// Ό³Έν :
class ABlock;
class UMoveObject
{
public:
	// constructor destructor
	UMoveObject();
	~UMoveObject();

	// delete Function
	UMoveObject(const UMoveObject& _Other) = delete;
	UMoveObject(UMoveObject&& _Other) noexcept = delete;
	UMoveObject& operator=(const UMoveObject& _Other) = delete;
	UMoveObject& operator=(UMoveObject&& _Other) noexcept = delete;

protected:
	void MoveSetOwner(ABlock* _Owner);

	ABlock* GetOwner()
	{
		return MoveOwner;
	}


private:
	ABlock* MoveOwner = nullptr;
};

