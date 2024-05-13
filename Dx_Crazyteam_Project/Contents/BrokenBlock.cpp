#include "PreCompile.h"
#include "BrokenBlock.h"
#include <EngineCore/DefaultSceneComponent.h>

ABrokenBlock::ABrokenBlock()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);
	
	FrontRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	FrontRenderer->SetupAttachment(Root);
}

ABrokenBlock::~ABrokenBlock()
{
}

void ABrokenBlock::BeginPlay()
{
	Super::BeginPlay();
	StateInit();
	CreateAnimation();
}

void ABrokenBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
}

void ABrokenBlock::StateInit()
{
	State.CreateState("None");
	State.CreateState("Idle");
	State.CreateState("Break");
	State.CreateState("End");

	State.SetStartFunction("None", std::bind(&ABrokenBlock::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&ABrokenBlock::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Idle",
		std::bind(&ABrokenBlock::IdleBegin, this),
		std::bind(&ABrokenBlock::IdleTick, this, std::placeholders::_1),
		std::bind(&ABrokenBlock::IdleExit, this));
	State.SetFunction("Break",
		std::bind(&ABrokenBlock::BreakBegin, this),
		std::bind(&ABrokenBlock::BreakTick, this, std::placeholders::_1),
		std::bind(&ABrokenBlock::BreakExit, this));
	State.SetFunction("End",
		std::bind(&ABrokenBlock::EndBegin, this),
		std::bind(&ABrokenBlock::EndTick, this, std::placeholders::_1),
		std::bind(&ABrokenBlock::EndExit, this));

	State.ChangeState("None");
}

void ABrokenBlock::CreateAnimation()
{
	//FrontRenderer->CreateAnimation("Idle", )
}

// None
void ABrokenBlock::NoneBegin()
{
}

void ABrokenBlock::NoneTick(float _DeltaTime)
{
}


#pragma region Idle
void ABrokenBlock::IdleBegin()
{
}

void ABrokenBlock::IdleTick(float _DeltaTime)
{
}

void ABrokenBlock::IdleExit()
{
}
#pragma endregion


#pragma region Break
void ABrokenBlock::BreakBegin()
{
}


void ABrokenBlock::BreakTick(float _DeltaTime)
{
}

void ABrokenBlock::BreakExit()
{
}
#pragma endregion

#pragma region End
void ABrokenBlock::EndBegin()
{
}

void ABrokenBlock::EndTick(float _DeltaTime)
{
}

void ABrokenBlock::EndExit()
{
}
#pragma endregion