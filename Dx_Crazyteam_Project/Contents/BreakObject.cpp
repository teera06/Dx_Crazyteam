#include "PreCompile.h"
#include "BreakObject.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Block.h"
#include "Bush.h"

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

		if (BreakOwner->GetType() == EMapObjectType::Bush)
		{
			ABush* Bush = dynamic_cast<ABush*>(BreakOwner);

			if (Bush->GetPossessBlock() == nullptr)
			{
				BreakOwner->MinusHP();

				if (BreakOwner->GetHp() <= 0)
				{
					BreakOwner->SetIsBreak(true);
				}
			}
			else
			{
				Bush->GetPossessBlock()->WaterInteract();
			}
		}
		else
		{
			BreakOwner->MinusHP();

			if (BreakOwner->GetHp() <= 0)
			{
				BreakOwner->SetIsBreak(true);
			}
		}


		};

}