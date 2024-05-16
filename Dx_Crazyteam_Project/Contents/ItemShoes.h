#pragma once
#include "Item.h"

// Ό³Έν :
class AItemShoes : public AItem
{
	GENERATED_BODY(AItem)
public:
	// constructor destructor
	AItemShoes();
	~AItemShoes();

	// delete Function
	AItemShoes(const AItemShoes& _Other) = delete;
	AItemShoes(AItemShoes&& _Other) noexcept = delete;
	AItemShoes& operator=(const AItemShoes& _Other) = delete;
	AItemShoes& operator=(AItemShoes&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
private:

};

