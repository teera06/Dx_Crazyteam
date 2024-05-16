#include "PreCompile.h"
#include "WaterBomb.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "WaterCourse.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "Packets.h"
#include "Game_Core.h"

int AWaterBomb::WaterBomb_Token = 0;

AWaterBomb::AWaterBomb()
{
	//UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	//SetRoot(Root);

	//Renderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	//Renderer->SetupAttachment(Root);

	int TestValue = GetObjectToken();
	SetObjectToken(GetObjectToken() + (1));
}

AWaterBomb::~AWaterBomb()
{
}

void AWaterBomb::BeginPlay()
{
	Super::BeginPlay();
	StateInit();
	CreateAnimation();
	SetActorScale3D(FVector(20, 20, 1));
	Renderer->SetPosition(FVector(0.0f, -1.0f));
	Renderer->SetAutoSize(0.05f, true);
	Renderer->SetOrder(ERenderOrder::Player);
	//Renderer->SetPivot(EPivot::BOT);
	//Renderer->SetActive(false);
	SetType(EMapObjectType::WaterBalloon);
}

void AWaterBomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);


	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UGame_Core::Net)
		{
			InitNet(UGame_Core::Net);
		}
	}

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->AnimationInfo = Renderer->GetCurAnimationFrame();
		Packet->SpriteName = Renderer->GetCurInfo().Texture->GetName();
		Packet->IsDestroy = b_ServerBomb;
		Send(Packet);
		CurTime += FrameTime;
	}

	///WaterBombPacket(_DeltaTime, b_ServerBomb);
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
	Renderer->SetActive(true);
	LifeTime = 0.0f;
}

void AWaterBomb::CreateTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;
	if (2.0f <= LifeTime || true == b_WaterToBomb)
	{
		State.ChangeState("Bomb");
		return;
	}
}

void AWaterBomb::CreateExit()
{
	LifeTime = 0.0f;
	//Renderer->SetActive(false);
}





void AWaterBomb::BombBegin()
{
	GetGameMode()->GetCurMap()->AddMapObject(GetCurPos().y, GetCurPos().x, EMapObject::Water);
	b_ServerBomb = true;
}

void AWaterBomb::BombTick(float _DeltaTime)
{
	//Destroy();
	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}

void AWaterBomb::BombExit()
{
}
