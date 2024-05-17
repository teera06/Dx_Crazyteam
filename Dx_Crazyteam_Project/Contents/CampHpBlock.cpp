#include "PreCompile.h"
#include "CampHpBlock.h"

ACampHpBlock::ACampHpBlock() 
{
}

ACampHpBlock::~ACampHpBlock() 
{
}

void ACampHpBlock::BeginPlay()
{
	Super::BeginPlay();

	BreakSetOwner(this);
	MoveSetOwner(this);
	
	SetHp(3);
}

void ACampHpBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int Hp = BreakOwner->GetHp();

	switch (Hp)
	{
	case 3:
		Renderer->SetSprite("CampHpBlock_0.png");
		break;
	case 2:
		Renderer->SetSprite("CampHpBlock_1.png");
		break;
	case 1:
		Renderer->SetSprite("CampHpBlock_2.png");
		break;
	}
}

