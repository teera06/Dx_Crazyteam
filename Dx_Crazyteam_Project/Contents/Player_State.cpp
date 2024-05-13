#include "PreCompile.h"
#include "Player.h"
#include "BaseMap.h"

void APlayer::StateInit()
{
	//여기서 랜더러 CreateAnimation 등 해줘야함.

	InputOn();


	// CreateState
	State.CreateState("Idle");
	State.CreateState("Move");
	//State.CreateState("Attack");
	//State.CreateState("Die");

	// StartFunction
	State.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));
	State.SetStartFunction("Move", std::bind(&APlayer::MoveStart, this));

	// UpdateFunction
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Move", std::bind(&APlayer::Move, this, std::placeholders::_1));

	// ChangeState
	State.ChangeState("Idle");
}

void APlayer::IdleStart()
{
	//Renderer->ChangeAnimation("Idle");
}

void  APlayer::Idle(float _DeltaTime)
{
	if (true == IsPress(VK_UP) || true == IsPress(VK_DOWN) || true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
	{
		State.ChangeState("Move");
		return;
	}
}

void APlayer::MoveStart()
{
	//Renderer->ChangeAnimation("Move");
}

void APlayer::Move(float _DeltaTime)
{
	FVector MovePos = FVector::Zero;
	FVector NextPos = FVector::Zero;

	if (true == IsPress(VK_UP))
	{
		MovePos = FVector::Up * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_DOWN))
	{
		MovePos = FVector::Down * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_RIGHT))
	{
		MovePos = FVector::Right * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_LEFT))
	{
		MovePos = FVector::Left * Info->MoveSpeed * _DeltaTime;
	}

	NextPos = GetActorLocation() + MovePos;

	if (true == ABaseMap::IsMove(NextPos))
	{
		AddActorLocation(MovePos);
	}
}
