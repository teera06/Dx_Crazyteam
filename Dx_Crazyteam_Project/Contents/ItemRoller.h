#pragma once
#include "Item.h"

// 설명 : 속도 빨라지는 아이템
class AItemRoller : public AItem
{
	GENERATED_BODY(AItem)

public : 
	AItemRoller();
	~AItemRoller();

	AItemRoller(const AItemRoller& _Other)				 = delete;
	AItemRoller(AItemRoller& _Other) noexcept				 = delete;
	AItemRoller& operator =(const AItemRoller& _Other)	 = delete;
	AItemRoller& operator =(AItemRoller& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
private:
};

