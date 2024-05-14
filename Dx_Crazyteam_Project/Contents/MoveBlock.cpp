#include "PreCompile.h"
#include "MoveBlock.h"

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
		};
}

void AMoveBlock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMoveBlock::StateInit()
{
	State.CreateState("None");
	State.CreateState("Idle");
	State.CreateState("Push");
	State.CreateState("End");

	State.ChangeState("Idle");
}

void AMoveBlock::CreateAnimation()
{
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
		State.ChangeState("Push");
		return;
	}
}

void AMoveBlock::IdleExit()
{
}

void AMoveBlock::PushBegin()
{
}

void AMoveBlock::PushTick(float _DeltaTime)
{

}

void AMoveBlock::PushExit()
{
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

