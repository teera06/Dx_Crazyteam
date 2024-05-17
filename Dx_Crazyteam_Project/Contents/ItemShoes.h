#pragma once
#include "Item.h"

// 설명 : 물풍선 킥할 수 있는 아이템
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

