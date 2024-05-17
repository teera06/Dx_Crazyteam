#include "PreCompile.h"
#include "BreakObject.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Block.h"

UBreakObject::UBreakObject()
{

}

UBreakObject::~UBreakObject()
{
}

void UBreakObject::BreakSetOwner(ABlock* _Owner)
{
	BreakOwner = _Owner;
	BreakOwner->WaterInteract = [&]() {

		if (BreakOwner->GetIsBreak() == true) return;

		BreakOwner->MinusHP();

		if (BreakOwner->GetHp() <= 0)
		{
			BreakOwner->SetIsBreak(true);
		}

		};
}