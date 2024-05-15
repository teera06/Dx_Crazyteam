#include "PreCompile.h"
#include "BrokenBlock.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "CAGameMode.h"
#include "BaseMap.h"

ABrokenBlock::ABrokenBlock()
{

}

ABrokenBlock::~ABrokenBlock()
{
}

void ABrokenBlock::BeginPlay()
{
	Super::BeginPlay();
	StateInit();
	CreateAnimation();
	SetType(EMapObjectType::BrakableBlock);

	WaterInteract = [&]() {
		IsBreak = true;
		};
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

	State.ChangeState("Idle");
}

void ABrokenBlock::CreateAnimation()
{

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
	if (IsBreak)
	{
		State.ChangeState("Break");
		return;
	}
}

void ABrokenBlock::IdleExit()
{
}
#pragma endregion


#pragma region Break
void ABrokenBlock::BreakBegin()
{
	AccTime = 0.f;
}


void ABrokenBlock::BreakTick(float _DeltaTime)
{
	AccTime += _DeltaTime;
	if (AccTime > BreakBlockTime)
	{
		State.ChangeState("End");
		return;
	}

	AccBlinkTime += _DeltaTime;
	if (AccBlinkTime > BlinkTime)
	{
		if (BlinkOn)
		{
			FrontRenderer->SetActive(false);
			BackRenderer->SetActive(false);
		}
		else
		{
			FrontRenderer->SetActive(true);
			BackRenderer->SetActive(true);
		}
	}
}

void ABrokenBlock::BreakExit()
{
}
#pragma endregion

#pragma region End
void ABrokenBlock::EndBegin()
{
	GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
}

void ABrokenBlock::EndTick(float _DeltaTime)
{
}

void ABrokenBlock::EndExit()
{
}
#pragma endregion