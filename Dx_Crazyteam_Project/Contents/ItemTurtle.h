#pragma once
#include "Item.h"

// Ό³Έν :
class AItemTurtle : public AItem
{
	GENERATED_BODY(AItem)
public:
	// constructor destructor
	AItemTurtle();
	~AItemTurtle();

	// delete Function
	AItemTurtle(const AItemTurtle& _Other) = delete;
	AItemTurtle(AItemTurtle&& _Other) noexcept = delete;
	AItemTurtle& operator=(const AItemTurtle& _Other) = delete;
	AItemTurtle& operator=(AItemTurtle&& _Other) noexcept = delete;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;
private:

};

