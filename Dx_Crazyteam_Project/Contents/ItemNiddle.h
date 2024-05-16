#pragma once
#include "Item.h"

class AItemNiddle : public AItem
{
	GENERATED_BODY(AItem)

public : 
	AItemNiddle();
	~AItemNiddle();

	AItemNiddle(const AItemNiddle& _Other)				 = delete;
	AItemNiddle(AItemNiddle& _Other) noexcept				 = delete;
	AItemNiddle& operator =(const AItemNiddle& _Other)	 = delete;
	AItemNiddle& operator =(AItemNiddle& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

