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

			POINT PlayerIndex = GetGameMode()->GetPlayer()->GetPlayerInfo()->CurIndex;

			if (PlayerIndex.x == GetCurPos().x)
			{
				if (PlayerIndex.y < GetCurPos().y)
				{
					SetPushDir(ECADir::Down);
				}
				else if (PlayerIndex.y > GetCurPos().y)
				{
					SetPushDir(ECADir::Up);
				}
			}
			else if (PlayerIndex.y == GetCurPos().y)
			{
				if (PlayerIndex.x < GetCurPos().x)
				{
					SetPushDir(ECADir::Right);
				}
				else if (PlayerIndex.x > GetCurPos().x)
				{
					SetPushDir(ECADir::Left);
				}
			}

			switch (GetPushDir())
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

			//State.ChangeState("Kick");
		};
}

void AWaterBomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);

#ifdef _DEBUG
	std::string WaterBombMsg = std::format("Water Bomb {}\n", GetActorLocation().ToString());


	UMapDebugGUI::PushMsg(WaterBombMsg);
#endif
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
}
void AWaterBomb::KickTick(float _DeltaTime)
{
	AddActorLocation(MoveVector * KickSpeed * _DeltaTime);

	FVector CheckPos = GetActorLocation() + MoveVector * 30.f;

	POINT CurPoint = GetGameMode()->GetCurMap()->PosToPoint(GetActorLocation());
	POINT CheckPoint = GetGameMode()->GetCurMap()->PosToPoint(CheckPos);

	
	
}
void AWaterBomb::KickExit()
{
}




void AWaterBomb::BombBegin()
{
	{
		if (true == GetIsPossessed())
		{
			GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
		}

		GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Water);

		if (true == GetIsPossessed())
		{
			Destroy();
		}
	}
}

void AWaterBomb::BombTick(float _DeltaTime)
{
}

void AWaterBomb::BombExit()
{
}
