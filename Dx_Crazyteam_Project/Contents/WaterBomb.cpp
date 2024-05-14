#include "PreCompile.h"
#include "WaterBomb.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "WaterCourse.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "Packets.h"
#include "Game_Core.h"

AWaterBomb::AWaterBomb()
{
	//UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	//SetRoot(Root);

	//Renderer = CreateDefaultSubObject<USpriteRenderer>("Render");
	//Renderer->SetupAttachment(Root);
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
	Renderer->SetAutoSize(0.05f, true);
	Renderer->SetOrder(ERenderOrder::Player);
	//Renderer->SetPivot(EPivot::BOT);
	//Renderer->SetActive(false);
}

void AWaterBomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);

	

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
	//std::shared_ptr<AWaterCourse> Course = GetWorld()->SpawnActor<AWaterCourse>("WaterCourse");
	////Course->SetPowerValue(Power);
	//Course->SetPowerValue(5);
	//Course->SetBombPoint(CurPos);
	//Course->CreateWaterCenter();

	GetGameMode()->GetCurMap()->AddMapObject(CurPos.y, CurPos.x, EMapObject::Water);
	b_ServerBomb = true;
}

void AWaterBomb::BombTick(float _DeltaTime)
{
	//Destroy();
}

void AWaterBomb::BombExit()
{
}
