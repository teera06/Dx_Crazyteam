#include "PreCompile.h"
#include "MoveObject.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Block.h"
#include "Bush.h"

UMoveObject::UMoveObject() 
{
}

UMoveObject::~UMoveObject() 
{
}

void UMoveObject::MoveSetOwner(ABlock* _Owner)
{
	MoveOwner = _Owner;
	MoveOwner->PlayerInteract = [&]() {

		if (GetOwner()->GetIsPush()) return;

		if (GetOwner()->GetType() == EMapObjectType::Bush)
		{
			ABush* Bush = dynamic_cast<ABush*>(GetOwner());

			if (Bush->GetPossessBlock() == nullptr)
			{
				return;
			}
			else
			{
				Bush->GetPossessBlock()->PlayerInteract();
			}
		}
		else
		{
			GetOwner()->SetIsPush(true);
		}

		};
}


