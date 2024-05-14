#include "PreCompile.h"
#include "Player.h"
#include "BaseMap.h"
#include "CAGameMode.h"

void APlayer::StateInit()
{
	InputOn();

	// CreateAnimation
	Renderer->CreateAnimation("Bazzi_Idle_Up", "bazzi_idle.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Bazzi_Idle_Down", "bazzi_idle.png", AnimationInter, false, 1, 1);
	Renderer->CreateAnimation("Bazzi_Idle_Right", "bazzi_idle.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Bazzi_Idle_Left", "bazzi_idle.png", AnimationInter, false, 3, 3);
	Renderer->CreateAnimation("Bazzi_Move_Left", "bazzi_left.png", AnimationInter,true, 0, 3);
	Renderer->CreateAnimation("Bazzi_Move_Right", "bazzi_right.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Bazzi_Move_Up", "bazzi_up.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Bazzi_Move_Down", "bazzi_down.png", AnimationInter, true, 0, 3);

	Renderer->CreateAnimation("Dao_Idle_Up", "dao_idle.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Dao_Idle_Down", "dao_idle.png", AnimationInter, false, 1, 1);
	Renderer->CreateAnimation("Dao_Idle_Right", "dao_idle.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Dao_Idle_Left", "dao_idle.png", AnimationInter, false, 3, 3);
	Renderer->CreateAnimation("Dao_Move_Left", "dao_left.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Dao_Move_Right", "dao_right.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Dao_Move_Up", "dao_up.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Dao_Move_Down", "dao_down.png", AnimationInter, true, 0, 3);

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
	FVector NextPos1 = FVector::Zero;	// Center
	FVector NextPos2 = FVector::Zero;	// 추가 체크포인트
	FVector NextPos3 = FVector::Zero;	// 추가 체크포인트

	if (true == IsPress(VK_UP))
	{
		Dir = FVector::Up;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Up * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_DOWN))
	{
		Dir = FVector::Down;
		NextPos1 = GetActorLocation() + MovePos + Dir * 5.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Down * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_RIGHT))
	{
		Dir = FVector::Right;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Right * Info->MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_LEFT))
	{
		Dir = FVector::Left;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Left * Info->MoveSpeed * _DeltaTime;
	}

	Renderer->ChangeAnimation(GetAnimationName("Move"));
	if (true == GetGameMode()->GetCurMap()->IsMove(NextPos1) && true == GetGameMode()->GetCurMap()->IsMove(NextPos2) && true == GetGameMode()->GetCurMap()->IsMove(NextPos3))
	{
		AddActorLocation(MovePos);
		return;
	}
}
