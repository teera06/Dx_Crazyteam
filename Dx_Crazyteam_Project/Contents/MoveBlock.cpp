#include "PreCompile.h"
#include "MoveBlock.h"
#include "Player.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AMoveBlock::AMoveBlock() 
{
}

AMoveBlock::~AMoveBlock() 
{
}

void AMoveBlock::BeginPlay()
{
	Super::BeginPlay();

	Type = EMapObjectType::MoveBlock;

	PlayerInteract = [&]() {
		IsPush = true;
		PlayerIndex = GetGameMode()->GetPlayer()->GetPlayerInfo()->CurIndex;

		if (PlayerIndex.x == CurPos.x)
		{
			if (PlayerIndex.y < CurPos.y)
			{
				MoveDir = ECADir::Down;
			}
			else
			{
				MoveDir = ECADir::Up;
			}
		}
		else if (PlayerIndex.y == CurPos.y)
		{
			if (PlayerIndex.x < CurPos.x)
			{
				MoveDir = ECADir::Right;
			}
			else
			{
				MoveDir = ECADir::Left;
			}
		}
		};

	StateInit();
}

void AMoveBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
}

void AMoveBlock::StateInit()
{
	State.CreateState("None");
	State.CreateState("Idle");
	State.CreateState("Push");
	State.CreateState("End");

	State.SetStartFunction("None", std::bind(&AMoveBlock::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&AMoveBlock::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Idle",
		std::bind(&AMoveBlock::IdleBegin, this),
		std::bind(&AMoveBlock::IdleTick, this, std::placeholders::_1),
		std::bind(&AMoveBlock::IdleExit, this));
	State.SetFunction("Push",
		std::bind(&AMoveBlock:: PushBegin, this),
		std::bind(&AMoveBlock:: PushTick, this, std::placeholders::_1),
		std::bind(&AMoveBlock:: PushExit, this));
	State.SetFunction("End",
		std::bind(&AMoveBlock::EndBegin, this),
		std::bind(&AMoveBlock::EndTick, this, std::placeholders::_1),
		std::bind(&AMoveBlock::EndExit, this));

	State.ChangeState("Idle");
}

void AMoveBlock::NoneBegin()
{
}

void AMoveBlock::NoneTick(float _DeltaTime)
{
}

void AMoveBlock::IdleBegin()
{
}

void AMoveBlock::IdleTick(float _DeltaTime)
{
	if (IsPush)
	{
		int Order = 0;
		switch (MoveDir)
		{
		case ECADir::Up:
			Order = 0;
			break;
		case ECADir::Right:
			Order = 1;
			break;
		case ECADir::Down:
			Order = 2;
			break;
		case ECADir::Left:
			Order = 3;
			break;
		}

		nx = CurPos.x + dx[Order];
		ny = CurPos.y + dy[Order];

		if (nx < 0 || ny < 0 || nx >= ConstValue::TileX || ny >= ConstValue::TileY - 1)
		{
			IsPush = false;
			return;
		}

		if (!GetGameMode()->GetCurMap()->IsEmpty(ny, nx))
		{
			IsPush = false;
			return;
		}

		State.ChangeState("Push");
		return;
	}
}

void AMoveBlock::IdleExit()
{
}

void AMoveBlock::PushBegin()
{
	GetGameMode()->GetCurMap()->AddMapObject(ny, nx, EMapObject::DummyBlock);
}

void AMoveBlock::PushTick(float _DeltaTime)
{
	FVector MoveVector = FVector::Zero;

	switch (MoveDir)
	{
	case ECADir::Up:
		MoveVector = FVector::Up;
		break;
	case ECADir::Right:
		MoveVector = FVector::Right;
		break;
	case ECADir::Down:
		MoveVector = FVector::Down;
		break;
	case ECADir::Left:
		MoveVector = FVector::Left;
		break;
	}

	FrontRenderer->AddPosition(MoveVector * MoveSpeed * _DeltaTime);
	BackRenderer->AddPosition(MoveVector * MoveSpeed * _DeltaTime);

	AccTime += _DeltaTime;
	if (AccTime > MoveCompleteTime)
	{
		State.ChangeState("End");
		return;
	}
}

void AMoveBlock::PushExit()
{
	GetGameMode()->GetCurMap()->DestroyMapObject(CurPos.y,CurPos.x);
	GetGameMode()->GetCurMap()->AddMapObject(ny, nx,EMapObject::CampMoveBlock);

	IsPush = false;
}

void AMoveBlock::EndBegin()
{
}

void AMoveBlock::EndTick(float _DeltaTime)
{

}

void AMoveBlock::EndExit()
{
}

