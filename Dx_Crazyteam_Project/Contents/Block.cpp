#include "PreCompile.h"
#include "Block.h"
#include "CAGameMode.h"
#include "BaseMap.h"
#include "Bush.h"
#include "Player.h"
#include "OtherPlayer.h"
#include <EngineBase/EngineRandom.h>

#include "Game_Core.h"
#include "SendPacketManager.h"

ABlock::ABlock() 
{
}

ABlock::~ABlock() 
{
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();

	SetType(EMapObjectType::Block);

	Renderer->SetPivot(EPivot::BOT);
	Renderer->SetOrder(ERenderOrder::WaterBomb);
	Renderer->AddPosition(FVector::Down * 20.f);
	Renderer->SetAutoSize(1.f, true);

	StateInit();
}

void ABlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	BushCheck();
}

void ABlock::StateInit()
{
	State.CreateState("None");
	State.CreateState("Idle");
	State.CreateState("Break");
	State.CreateState("Push");
	State.CreateState("End");

	State.SetStartFunction("None", std::bind(&ABlock::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&ABlock::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Idle",
		std::bind(&ABlock::IdleBegin, this),
		std::bind(&ABlock::IdleTick, this, std::placeholders::_1),
		std::bind(&ABlock::IdleExit, this));
	State.SetFunction("End",
		std::bind(&ABlock::EndBegin, this),
		std::bind(&ABlock::EndTick, this, std::placeholders::_1),
		std::bind(&ABlock::EndExit, this));

	State.SetFunction("Break",
		std::bind(&ABlock::BreakBegin, this),
		std::bind(&ABlock::BreakTick, this, std::placeholders::_1),
		std::bind(&ABlock::BreakExit, this));

	State.SetFunction("Push",
		std::bind(&ABlock::PushBegin, this),
		std::bind(&ABlock::PushTick, this, std::placeholders::_1),
		std::bind(&ABlock::PushExit, this));

	State.ChangeState("Idle");
}

void ABlock::CreateAnimation()
{

}

// None
void ABlock::NoneBegin()
{
}

void ABlock::NoneTick(float _DeltaTime)
{
}


void ABlock::IdleBegin()
{
}

void ABlock::IdleTick(float _DeltaTime)
{
	if (IsBreak)
	{
		State.ChangeState("Break");
		return;
	}

	if (IsPush)
	{
		FVector PlayerDir = GetGameMode()->GetPlayer()->GetDir();
		MoveDir = PlayerDir;

		nx = GetCurPos().x + static_cast<int>(MoveDir.X);
		ny = GetCurPos().y - static_cast<int>(MoveDir.Y);

		if (nx < 0 || ny < 0 || nx >= ConstValue::TileX || ny >= ConstValue::TileY - 1)
		{
			IsPush = false;
			return;
		}

		for (int i = 0; i < GetGameMode()->GetOtherPlayers().size(); i++)
		{
			POINT CheckPos = GetGameMode()->GetCurMap()->PosToPoint(GetGameMode()->GetOtherPlayers()[i]->GetActorLocation());

			if (ny == CheckPos.y &&
				nx == CheckPos.x)
			{
				IsPush = false;
				return;
			}
		}
		

		if (!GetGameMode()->GetCurMap()->IsEmpty(ny, nx))
		{
			if (GetGameMode()->GetCurMap()->GetMapObject(ny, nx)->GetType() == EMapObjectType::Bush)
			{
				ABush* Bush = dynamic_cast<ABush*>(GetGameMode()->GetCurMap()->GetMapObject(ny, nx).get());

				if (Bush->GetPossessBlock() != nullptr)
				{
					IsPush = false;
					return;
				}
			}
			else if (GetGameMode()->GetCurMap()->GetMapObject(ny, nx)->GetType() == EMapObjectType::Item)
			{
				IsPush = true;
			}
			else
			{
				IsPush = false;
				return;
			}

		}


		State.ChangeState("Push");
		return;
	}


}

void ABlock::IdleExit()
{
}

void ABlock::BreakBegin()
{

}


void ABlock::BreakTick(float _DeltaTime)
{
	if (GetType() == EMapObjectType::Bush)
	{
		State.ChangeState("End");
		return;
	}


	BreakAccTime += _DeltaTime;
	if (BreakAccTime > BreakBlockTime)
	{
		BreakAccTime = 0.f;
		State.ChangeState("End");
		return;
	}

	AccBlinkTime += _DeltaTime;
	if (AccBlinkTime > BlinkTime)
	{
		AccBlinkTime = 0.f;
		if (BlinkOn)
		{
			//Renderer->SetMulColor(FVector(1.f, 1.f, 1.f, 0.5f));
			Renderer->SetAlpha(0.5f);
			BlinkOn = false;
		}
		else
		{
			//Renderer->SetMulColor(FVector(1.f, 1.f, 1.f, 1.f));
			Renderer->SetAlpha(1.0f);
			BlinkOn = true;
		}
	}
}

void ABlock::BreakExit()
{
	
}

void ABlock::PushBegin()
{
	
}

void ABlock::PushTick(float _DeltaTime)
{

	AddActorLocation(MoveDir * MoveSpeed * _DeltaTime);

	// 블럭 이동 동기화
	{
		USendPacketManager::SendMapObjectMovePacket(this , GetActorLocation());
	}

	PushAccTime += _DeltaTime;
	if (PushAccTime > MoveCompleteTime)
	{
		PushAccTime = 0.f;
		State.ChangeState("End");
		return;
	}
}

void ABlock::PushExit()
{

}

void ABlock::EndBegin()
{

}
void ABlock::EndTick(float _DeltaTime)
{
	if (IsBreak)
	{
		if (GetPossessItem() == EItemType::None)
		{
			/*if (GetIsPossessed())
			{
				AMapObject* MapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x).get();
				
				ABush* Bush = dynamic_cast<ABush*>(MapObject);
				Bush->SetPossessBlock(nullptr);

				Destroy();
			}
			else
			{
			}*/
			GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
		}
		else
		{
			std::shared_ptr<UEngineServer> IsServer = dynamic_pointer_cast<UEngineServer>(UGame_Core::Net);

			//GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);

			if (nullptr != IsServer)
			{
				std::shared_ptr<AMapObject> Item = GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Item, GetPossessItem());
				USendPacketManager::SendMapObjectSpawnPacket(Item, { GetCurPos().y,GetCurPos().x }, EMapObject::Item, GetPossessItem());
			}

		}

		// 부서졌다면 푸시하지않음
		if (GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x) != nullptr &&
			GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x)->GetType() != EMapObjectType::Item)
		{
			GetGameMode()->GetCurMap()->ChangeNull(GetCurPos().y, GetCurPos().x);
		}

		Destroy();
		return;
	}


	if (IsPush)
	{
		//방지 if 코드
		if (!IsBreak)
		{
			// 블럭 이동 종료시 맵에서 좌표 동기화
			{
				USendPacketManager::SendMapObjectMoveEndPacket(shared_from_this(), ny, nx, GetCurPos().y, GetCurPos().x);
			}

			GetGameMode()->GetCurMap()->MoveMapObject(shared_from_this(), ny, nx, GetCurPos().y, GetCurPos().x);
		}

		IsPush = false;

		State.ChangeState("Idle");
	}
}
void ABlock::EndExit()
{

}

void ABlock::BushCheck()
{
	if (GetIsPossessed())
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}
}
