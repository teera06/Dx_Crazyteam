#include "PreCompile.h"
#include "WaterBomb.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "WaterCourse.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "Packets.h"
#include "Game_Core.h"
#include "MapDebugGUI.h"
#include <EngineBase/EngineTime.h>
#include <EngineCore/EngineDebugMsgWindow.h>
#include "MapStateValue.h"
#include "Bush.h"

#include "SendPacketManager.h"

#include "Player.h"

bool AWaterBomb::SetWater_CourseToken = false;
int AWaterBomb::WaterCourse_Token;

AWaterBomb::AWaterBomb()
{
	GetCreateTime();
	//UDefaultSceneComponent* wRoot = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	//SetRoot(wRoot);
	WaterBombRenderer = CreateDefaultSubObject<USpriteRenderer>("WaterBombRender");
	WaterBombRenderer->SetupAttachment(Root);
}

AWaterBomb::~AWaterBomb()
{
}

void AWaterBomb::BeginPlay()
{
	Super::BeginPlay();
	StateInit();
	CreateAnimation();
	//SetActorScale3D(FVector(20, 20, 1));
	//WaterBombRenderer->SetPosition(FVector(0.0f, -55.0f)); // 기본값으로 +20.0f 가 되어있음
	WaterBombRenderer->SetPosition(FVector(0.0f, -20.0f));
	WaterBombRenderer->SetAutoSize(1.0f, true);
	//Renderer->SetOrder(ERenderOrder::Player);
	//Renderer->SetPivot(EPivot::BOT);
	//Renderer->SetActive(false);
	SetType(EMapObjectType::WaterBalloon);
	//Renderer->SetSprite("Balloon.png");

	PlayerInteract = [&]
		{
			if (false == IsKick)
			{
				FVector PlayerDir = GetGameMode()->GetPlayer()->GetDir();
				MoveVector = PlayerDir;

				State.ChangeState("Kick");
				IsKick = true;
			}
		};
}

void AWaterBomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);

	std::string MSg = GetActorLocation().ToString();
	UEngineDebugMsgWindow::PushMsg(MSg);
}

float AWaterBomb::GetCreateTime()
{
	UEngineTime Time;
	Bomb_MilliSecond = Time.GetCurTime().MilliSecond;
	Bomb_Second = Time.GetCurTime().Second;
	return 0.0f;
}

void AWaterBomb::StateInit()
{
	State.CreateState("None");
	State.CreateState("Create");
	State.CreateState("Kick");
	State.CreateState("Bomb");

	State.SetStartFunction("None", std::bind(&AWaterBomb::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&AWaterBomb::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Create",
		std::bind(&AWaterBomb::CreateBegin, this),
		std::bind(&AWaterBomb::CreateTick, this, std::placeholders::_1),
		std::bind(&AWaterBomb::CreateExit, this));
	State.SetFunction("Kick",
		std::bind(&AWaterBomb::KickBegin, this),
		std::bind(&AWaterBomb::KickTick, this, std::placeholders::_1),
		std::bind(&AWaterBomb::KickExit, this));
	State.SetFunction("Bomb",
		std::bind(&AWaterBomb::BombBegin, this),
		std::bind(&AWaterBomb::BombTick, this, std::placeholders::_1),
		std::bind(&AWaterBomb::BombExit, this));

	State.ChangeState("None");
}

void AWaterBomb::CreateAnimation()
{
	//WaterCourseRender->CreateAnimation("Create", "bomb.png", 0.125f, true);
	WaterBombRenderer->CreateAnimation("Create", "bomb.png", 0.125f, true);

	WaterBombRenderer->ChangeAnimation("Create");
}


void AWaterBomb::NoneBegin()
{
	//b_Bomb = false;
}

void AWaterBomb::NoneTick(float _DeltaTime)
{
	int a = 0;
}


void AWaterBomb::CreateBegin()
{
	WaterBombThisGameMode = GetGameMode();
	WaterBombRenderer->SetActive(true);
	
	if (true == OtherCreate)
	{
		float Secound = static_cast<float>(Sub_Second);
		float MiliSecound = static_cast<float>(Sub_MilliSecond);
		MiliSecound /= 10000;
		ServerBombTime = BombTime - (Secound + MiliSecound); // 차이나는 만큼 빨리 터져라.
		LifeTime = 0.0f;
	}
	else
	{
		LifeTime = 0.0f;
	}
}

void AWaterBomb::CreateTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;

	if (false == OtherCreate)
	{
		if (BombTime <= LifeTime && false == b_WaterToBomb)
		{
			State.ChangeState("Bomb");
			return;
		}
		else if (true == b_WaterToBomb)
		{
			State.ChangeState("Bomb");
			return;
		}
	}
	else
	{
		//  2.0       0.0000000001
		if (ServerBombTime <= LifeTime)
		{
			State.ChangeState("Bomb");
			return;
		}
	}

}

void AWaterBomb::CreateExit()
{
	LifeTime = 0.0f;
	//Renderer->SetActive(false);
	ACAGameMode* CulGameModexx = GetGameMode();
	CulGameMode = CulGameModexx;
	int a = 0;
}





void AWaterBomb::KickBegin()
{
	TargetPoint = SearchLogic(GetCurPos(), MoveVector);

	std::shared_ptr<AMapObject> MapObj = GetGameMode()->GetCurMap()->GetMapObject(TargetPoint.y, TargetPoint.x);
	if (MapObj != nullptr)
	{
		if (MapObj->GetType() == EMapObjectType::Bush)
		{
			ABush* Bush = dynamic_cast<ABush*>(MapObj.get());
			SetIsPossessed(true);
			Bush->SetPossessBlock(shared_from_this());
		}
	}
	else
	{
		GetGameMode()->GetCurMap()->ConnectObject(shared_from_this(),TargetPoint.y, TargetPoint.x);
	}
	GetGameMode()->GetCurMap()->ChangeNull(GetCurPos().y, GetCurPos().x);
	SetCurPos(TargetPoint);
}
void AWaterBomb::KickTick(float _DeltaTime)
{
	AddActorLocation(MoveVector * KickSpeed * _DeltaTime);

	POINT CurPoint = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());

	if (CurPoint.y == TargetPoint.y &&
		CurPoint.x == TargetPoint.x)
	{
		FVector Pos = GetGameMode()->GetCurMap()->PointToPos(CurPoint.y, CurPoint.x);
		SetActorLocation(Pos);
		State.ChangeState("Create");
		return;
	}

}
void AWaterBomb::KickExit()
{
}

POINT AWaterBomb::SearchLogic(POINT _CurPoint, FVector _MoveVector)
{
	POINT NextPoint = _CurPoint;
	NextPoint.x += static_cast<int>(_MoveVector.X);
	NextPoint.y -= static_cast<int>(_MoveVector.Y);

	if (NextPoint.x > ConstValue::TileX-1 ||
		NextPoint.x < 0)
	{
		return _CurPoint;
	}

	if (NextPoint.y > ConstValue::TileY-2 ||
		NextPoint.y < 0)
	{
		return _CurPoint;
	}

	std::shared_ptr<AMapObject> MapObj = GetGameMode()->GetCurMap()->GetMapObject(NextPoint.y, NextPoint.x);

	if (MapObj != nullptr)
	{
		if (MapObj->GetType() == EMapObjectType::Block)
		{
			return _CurPoint;
		}

		if (MapObj->GetType() == EMapObjectType::WaterBalloon)
		{
			return _CurPoint;
		}

		if (MapObj->GetType() == EMapObjectType::Bush)
		{
			ABush* Bush = dynamic_cast<ABush*>(MapObj.get());
			if (Bush->GetPossessBlock())
			{
				return _CurPoint;
			}
		}
	}

	return SearchLogic(NextPoint, _MoveVector);
}


void AWaterBomb::BombBegin()
{
	{
		if (GetIsPossessed()) {
			GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
		}

		GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Water);
		//WaterCourse->SetObjectToken(GetObjectToken() + 10000);
		//USendPacketManager::SendMapObjectSpawnPacket(WaterCourse, { GetCurPos().y, GetCurPos().x}, EMapObject::Water);

		if (GetIsPossessed()) Destroy();
		//GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
	}
}

void AWaterBomb::BombTick(float _DeltaTime)
{
}

void AWaterBomb::BombExit()
{
}
