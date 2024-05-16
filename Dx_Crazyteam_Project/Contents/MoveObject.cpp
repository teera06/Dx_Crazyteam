#include "PreCompile.h"
#include "MoveObject.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Block.h"

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

		POINT PlayerIndex = GetOwner()->GetGameMode()->GetPlayer()->GetPlayerInfo()->CurIndex;

		if (PlayerIndex.x == GetOwner()->GetCurPos().x)
		{
			if (PlayerIndex.y < GetOwner()->GetCurPos().y)
			{
				GetOwner()->SetPushDir(ECADir::Down);
			}
			else
			{
				GetOwner()->SetPushDir(ECADir::Up);
			}
		}
		else if (PlayerIndex.y == GetOwner()->GetCurPos().y)
		{
			if (PlayerIndex.x < GetOwner()->GetCurPos().x)
			{
				GetOwner()->SetPushDir(ECADir::Right);
			}
			else
			{
				GetOwner()->SetPushDir(ECADir::Left);
			}
		}

		GetOwner()->SetIsPush(true);
		};
}

