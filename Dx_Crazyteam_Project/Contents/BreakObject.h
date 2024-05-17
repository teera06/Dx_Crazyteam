#pragma once
class ABlock;
class UBreakObject
{
public:
	// constructor destructor
	UBreakObject();
	~UBreakObject();

	// delete Function
	UBreakObject(const UBreakObject& _Other) = delete;
	UBreakObject(UBreakObject&& _Other) noexcept = delete;
	UBreakObject& operator=(const UBreakObject& _Other) = delete;
	UBreakObject& operator=(UBreakObject&& _Other) noexcept = delete;

	void BreakSetOwner(ABlock* _Owner);
	void DamageLogic();

	ABlock* GetOwner()
	{
		return BreakOwner;
	}

	ABlock* BreakOwner = nullptr;
private:

};

