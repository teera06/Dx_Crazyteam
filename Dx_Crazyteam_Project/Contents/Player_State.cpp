#include "PreCompile.h"
#include "Player.h"
#include "BaseMap.h"

void APlayer::StateInit()
{
	InputOn();

	// CreateAnimation
	Renderer->CreateAnimation("Idle_Left", "bazzi_left.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Idle_Right", "bazzi_right.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Idle_Up", "bazzi_up.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Idle_Down", "bazzi_down.png", AnimationInter, false, 0, 0);

	Renderer->CreateAnimation("Move_Left", "bazzi_left.png", AnimationInter,true, 0, 5);
	Renderer->CreateAnimation("Move_Right", "bazzi_right.png", AnimationInter, true, 0, 5);
	Renderer->CreateAnimation("Move_Up", "bazzi_up.png", AnimationInter, true, 0, 7);
	Renderer->CreateAnimation("Move_Down", "bazzi_down.png", AnimationInter, true, 0, 7);

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

	// Init
	State.ChangeState("Idle");
}

void APlayer::IdleStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Idle"));
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
	
}

void APlayer::Move(float _DeltaTime)
{
	if (true == IsFree(VK_UP) && true == IsFree(VK_DOWN) && true == IsFree(VK_RIGHT) && true == IsFree(VK_LEFT))
	{
		State.ChangeState("Idle");
		return;
	}

	FVector MovePos = FVector::Zero;
	FVector NextPos = FVector::Zero;

	if (true == IsPress(VK_UP))
	{
		Dir = FVector::Up;
		MovePos = FVector::Up * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_DOWN))
	{
		Dir = FVector::Down;
		MovePos = FVector::Down * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_RIGHT))
	{
		Dir = FVector::Right;
		MovePos = FVector::Right * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_LEFT))
	{
		Dir = FVector::Left;
		MovePos = FVector::Left * Info->MoveSpeed * _DeltaTime;
	}

	NextPos = GetActorLocation() + MovePos + Dir * 10.f;

	Renderer->ChangeAnimation(GetAnimationName("Move"));
	if (true == ABaseMap::IsMove(NextPos))
	{
		AddActorLocation(MovePos);
		return;
	}
}
