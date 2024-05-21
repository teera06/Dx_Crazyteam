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
	Renderer->SetPosition(FVector(0.0f, -55.0f)); // 기본값으로 +20.0f 가 되어있음
	Renderer->SetAutoSize(1.0f, true);
	//Renderer->SetOrder(ERenderOrder::Player);
	//Renderer->SetPivot(EPivot::BOT);
	//Renderer->SetActive(false);
	SetType(EMapObjectType::WaterBalloon);
	//Renderer->SetSprite("Balloon.png");

	PlayerInteract = [&]
		{
			if (GetIsPush()) return;
			SetIsPush(true);
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
	Renderer->CreateAnimation("Create", "bomb.png", 0.125f, true);

	Renderer->ChangeAnimation("Create");
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
	Renderer->SetActive(true);
	
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
	//Renderer->SetActive(false);
	//b_ServerBomb = BombServer;

	{
		if (GetIsPossessed()) GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);

		std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Water));		
		WaterCourse->SetObjectToken(GetObjectToken() + 10000);
		USendPacketManager::SendMapObjectSpawnPacket(WaterCourse, { GetCurPos().y, GetCurPos().x}, EMapObject::Water);

		if (GetIsPossessed()) Destroy();
		//GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
	}
}

void AWaterBomb::BombTick(float _DeltaTime)
{
	//if (false == b_ServerBomb)
	//{
	//	std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Water));

	//	if (SetWater_CourseToken == false)
	//	{
	//		WaterCourse->WaterCourseToken = WaterCourse_Token;
	//		SetWater_CourseToken = true;
	//	}
	//	WaterCourse_Token = WaterCourse->WaterCourseToken++;
	//	WaterCourse->SetObjectToken(WaterCourse_Token);

	//	if (false == IsNetInit())
	//	{
	//		// 네트워크 통신준비가 아직 안된 오브젝트다.
	//		if (nullptr != UGame_Core::Net)
	//		{
	//			InitNet(UGame_Core::Net);
	//		}
	//	}
	//	std::shared_ptr<UWaterCourseUpdatePacket> Packet = std::make_shared<UWaterCourseUpdatePacket>();
	//	Packet->Pos = GetActorLocation();
	//	Packet->ObjectType = static_cast<int>(EObjectType::WaterCourse);
	//	Packet->Dir = 4;
	//	Packet->SetCourse = true;
	//	Send(Packet);

	//	b_ServerBomb = false;
	//}
	int a = 0;
}

void AWaterBomb::BombExit()
{
}
