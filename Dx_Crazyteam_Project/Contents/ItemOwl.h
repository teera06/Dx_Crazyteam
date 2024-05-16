#pragma once
#include "Item.h"

class AItemOwl : public AItem
{
	GENERATED_BODY(AItem)
public : 
	AItemOwl();
	~AItemOwl();

	AItemOwl(const AItemOwl& _Other)				 = delete;
	AItemOwl(AItemOwl& _Other) noexcept				 = delete;
	AItemOwl& operator =(const AItemOwl& _Other)	 = delete;
	AItemOwl& operator =(AItemOwl& _Other) noexcept	 = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};

