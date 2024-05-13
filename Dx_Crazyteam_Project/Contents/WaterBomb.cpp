#include "PreCompile.h"
#include "WaterBomb.h"
#include <EngineCore/DefaultSceneComponent.h>

AWaterBomb::AWaterBomb()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	WaterCourseRender = CreateDefaultSubObject<USpriteRenderer>("Render");
	WaterCourseRender->SetupAttachment(Root);
}

AWaterBomb::~AWaterBomb()
{
}

void AWaterBomb::BeginPlay()
{
	Super::BeginPlay();
	StateInit();
	CreateAnimation();

	WaterCourseRender->SetAutoSize(1.0f, true);
	WaterCourseRender->SetActive(false);
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
	WaterCourseRender->CreateAnimation("", "", 0.125f, true);
	WaterCourseRender->CreateAnimation("", "", 0.125f, true);

	WaterCourseRender->ChangeAnimation("");
}


void AWaterBomb::NoneBegin()
{
	b_Bomb = false;
}

void AWaterBomb::NoneTick(float _DeltaTime)
{
}

void AWaterBomb::CreateBegin()
{
	WaterCourseRender->SetActive(true);
	LifeTime = 0.0f;
}

void AWaterBomb::CreateTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;
	if (2.0f <= LifeTime)
	{
		State.ChangeState("Bomb");
		return;
	}
}

void AWaterBomb::CreateExit()
{
	LifeTime = 0.0f;
}

void AWaterBomb::BombBegin()
{
	b_Bomb = true;
}

void AWaterBomb::BombTick(float _DeltaTime)
{
	// 애니메이션이 끝나면 Destroy();
}

void AWaterBomb::BombExit()
{
}
