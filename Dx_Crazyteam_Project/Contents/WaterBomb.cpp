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


bool AWaterBomb::SetWaterCourseToken = false;

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
}

void AWaterBomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);

	std::string MSg = GetActorLocation().ToString();
	UEngineDebugMsgWindow::PushMsg(MSg);

	//if (true == b_ServerBomb)
	//{
	//	std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Water));

	//	if (SetWaterCourseToken == false)
	//	{
	//		WaterCourse->WaterCourseToken = WaterCourse_Token;
	//		SetWaterCourseToken = true;
	//	}
	//	WaterCourse_Token = WaterCourse->WaterCourseToken;
	//	WaterCourse->SetObjectToken(WaterCourse_Token++);

	//	std::shared_ptr<UWaterWaterCourseUpdatePacket> Packet = std::make_shared<UWaterWaterCourseUpdatePacket>();
	//	std::string MSg = GetActorLocation().ToString();
	//	UEngineDebugMsgWindow::PushMsg(MSg);
	//	Packet->Pos = GetActorLocation();
	//	Packet->ObjectType = static_cast<int>(EObjectType::WaterCourse);
	//	Send(Packet);

	//	b_ServerBomb = false;
	//}
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
	State.CreateState("Bomb");

	State.SetStartFunction("None", std::bind(&AWaterBomb::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&AWaterBomb::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Create",
		std::bind(&AWaterBomb::CreateBegin, this),
		std::bind(&AWaterBomb::CreateTick, this, std::placeholders::_1),
		std::bind(&AWaterBomb::CreateExit, this));
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





void AWaterBomb::BombBegin()
{
	Renderer->SetActive(false);
	b_ServerBomb = BombServer;
}

void AWaterBomb::BombTick(float _DeltaTime)
{
	if (true == b_ServerBomb)
	{
		std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Water));

		if (SetWaterCourseToken == false)
		{
			WaterCourse->WaterCourseToken = WaterCourse_Token;
			SetWaterCourseToken = true;
		}
		WaterCourse_Token = WaterCourse->WaterCourseToken;
		WaterCourse->SetObjectToken(WaterCourse_Token++);

		std::shared_ptr<UWaterWaterCourseUpdatePacket> Packet = std::make_shared<UWaterWaterCourseUpdatePacket>();
		std::string MSg = GetActorLocation().ToString();
		UEngineDebugMsgWindow::PushMsg(MSg);
		Packet->Pos = GetActorLocation();
		Packet->ObjectType = static_cast<int>(EObjectType::WaterCourse);
		Send(Packet);

		b_ServerBomb = false;
	}
	//Destroy();
	//GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}

void AWaterBomb::BombExit()
{
}
