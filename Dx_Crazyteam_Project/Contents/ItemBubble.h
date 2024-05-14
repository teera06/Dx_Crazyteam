#pragma once
#include "Item.h"

class AItemBubble : public AItem
{
	GENERATED_BODY(AItem)
public:
	AItemBubble();
	~AItemBubble();

	AItemBubble(const AItemBubble& _Other) = delete;
	AItemBubble(AItemBubble&& _Other) noexcept = delete;
	AItemBubble& operator=(const AItemBubble& _Other) = delete;
	AItemBubble& operator=(AItemBubble&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

