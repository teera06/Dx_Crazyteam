#pragma once
#include "Item.h"

// Ό³Έν :
class AItemFluid : public AItem
{
	GENERATED_BODY(AItem)
public:
	// constructor destructor
	AItemFluid();
	~AItemFluid();

	// delete Function
	AItemFluid(const AItemFluid& _Other) = delete;
	AItemFluid(AItemFluid&& _Other) noexcept = delete;
	AItemFluid& operator=(const AItemFluid& _Other) = delete;
	AItemFluid& operator=(AItemFluid&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
private:

};

