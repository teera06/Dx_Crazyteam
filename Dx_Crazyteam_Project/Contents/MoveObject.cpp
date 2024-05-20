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

		POINT PlayerIndex = PlayerDirCheck();

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

POINT UMoveObject::PlayerDirCheck()
{
	POINT PlayerIndex = GetOwner()->GetGameMode()->GetPlayer()->GetPlayerInfo()->CurIndex;

	if (PlayerIndex.x == GetOwner()->GetCurPos().x)
	{
		if (PlayerIndex.y < GetOwner()->GetCurPos().y)
		{
			GetOwner()->SetPushDir(ECADir::Down);
		}
		else if(PlayerIndex.y > GetOwner()->GetCurPos().y)
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
		else if(PlayerIndex.x > GetOwner()->GetCurPos().x)
		{
			GetOwner()->SetPushDir(ECADir::Left);
		}
	}

	return PlayerIndex;
}

