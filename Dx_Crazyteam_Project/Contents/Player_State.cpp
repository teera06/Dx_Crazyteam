#include "PreCompile.h"
#include "Player.h"
#include "BaseMap.h"
#include "CAGameMode.h"
#include "Player_Shadow.h"

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
	Renderer->CreateAnimation("Bazzi_Trap", "bazzi_trap.png", AnimationInter * 2, true, 0, 1);
	Renderer->CreateAnimation("Bazzi_Trap_Last", "bazzi_trap.png", AnimationInter * 2, false, 2, 3);
	Renderer->CreateAnimation("Bazzi_Rescue", "bazzi_rescue.png", 0.1f, false, 0, 2);
	Renderer->CreateAnimation("Bazzi_Die", "bazzi_die.png", 0.1f, false, 0, 2);
	Renderer->CreateAnimation("Bazzi_Die_Last", "bazzi_die.png", 0.1f, false, 3, 4);

	Renderer->CreateAnimation("Dao_Idle_Up", "dao_idle.png", AnimationInter, false, 0, 0);
	Renderer->CreateAnimation("Dao_Idle_Down", "dao_idle.png", AnimationInter, false, 1, 1);
	Renderer->CreateAnimation("Dao_Idle_Right", "dao_idle.png", AnimationInter, false, 2, 2);
	Renderer->CreateAnimation("Dao_Idle_Left", "dao_idle.png", AnimationInter, false, 3, 3);
	Renderer->CreateAnimation("Dao_Move_Left", "dao_left.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Dao_Move_Right", "dao_right.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Dao_Move_Up", "dao_up.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Dao_Move_Down", "dao_down.png", AnimationInter, true, 0, 3);
	Renderer->CreateAnimation("Dao_Trap", "dao_trap.png", AnimationInter * 2, true, 0, 1);
	Renderer->CreateAnimation("Dao_Trap_Last", "dao_trap.png", AnimationInter * 2, false, 2, 3);
	Renderer->CreateAnimation("Dao_Rescue", "dao_rescue.png", 0.1f, false, 0, 2);
	Renderer->CreateAnimation("Dao_Die", "dao_die.png", 0.1f, false, 0, 2);
	Renderer->CreateAnimation("Dao_Die_Last", "dao_die.png", 0.1f, false, 3, 4);

	// CreateState
	State.CreateState("Idle");
	State.CreateState("Move");
	State.CreateState("Trap");
	State.CreateState("Rescue");
	State.CreateState("Die");
	State.CreateState("RealDie");

	// StartFunction
	State.SetStartFunction("Idle", std::bind(&APlayer::IdleStart, this));
	State.SetStartFunction("Move", std::bind(&APlayer::MoveStart, this));
	State.SetStartFunction("Trap", std::bind(&APlayer::TrapStart, this));
	State.SetStartFunction("Rescue", std::bind(&APlayer::RescueStart, this));
	State.SetStartFunction("Die", std::bind(&APlayer::DieStart, this));
	State.SetStartFunction("RealDie", std::bind(&APlayer::RealDieStart, this));

	// UpdateFunction
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetUpdateFunction("Move", std::bind(&APlayer::Move, this, std::placeholders::_1));
	State.SetUpdateFunction("Trap", std::bind(&APlayer::Trap, this, std::placeholders::_1));
	State.SetUpdateFunction("Rescue", std::bind(&APlayer::Rescue, this, std::placeholders::_1));
	State.SetUpdateFunction("Die", std::bind(&APlayer::Die, this, std::placeholders::_1));
	State.SetUpdateFunction("RealDie", std::bind(&APlayer::RealDie, this, std::placeholders::_1));

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

	float Speed = static_cast<float>(Info->Speed);

	if (true == IsPress(VK_UP))
	{
		Dir = FVector::Up;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Up * Speed * MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_DOWN))
	{
		Dir = FVector::Down;
		NextPos1 = GetActorLocation() + MovePos + Dir * 5.f;
		NextPos2 = NextPos1 + FVector(-15, 0, 0);
		NextPos3 = NextPos1 + FVector(15, 0, 0);
		MovePos = FVector::Down * Speed * MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_RIGHT))
	{
		Dir = FVector::Right;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Right * Speed * MoveSpeed * _DeltaTime;
	}
	if (true == IsPress(VK_LEFT))
	{
		Dir = FVector::Left;
		NextPos1 = GetActorLocation() + MovePos + Dir * 20.f;
		NextPos2 = NextPos1 + FVector(0, 10, 0);
		NextPos3 = NextPos1 + FVector(0, 0, 0);
		MovePos = FVector::Left * Speed * MoveSpeed * _DeltaTime;
	}

	Renderer->ChangeAnimation(GetAnimationName("Move"));
	if (true == GetGameMode()->GetCurMap()->IsMove(NextPos1) && true == GetGameMode()->GetCurMap()->IsMove(NextPos2) && true == GetGameMode()->GetCurMap()->IsMove(NextPos3))
	{
		AddActorLocation(MovePos);
		return;
	}
}

void APlayer::TrapStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Trap"));
	TrapDir = FVector::Up;
	TrapMoveTime = 1.f;
	TrapToDieTime = 5.f;
}


void APlayer::Trap(float _DeltaTime)
{
	// 이벤트 발생 시 구출 상태로 변경
	if (true == IsDown(VK_F2))	
	{
		Renderer->SetPosition(FVector::Zero);
		State.ChangeState("Rescue");
		return;
	}

	TrapMoveTime -= _DeltaTime;
	TrapAnimationTime -= _DeltaTime;
	TrapToDieTime -= _DeltaTime;


	// Renderer 상하로 움직이도록 Dir을 변경
	if (TrapMoveTime < 0.f)
	{
		TrapDir *= -1.f;
		TrapMoveTime = 1.f;
	}
	Renderer->AddPosition(TrapDir * TrapMoveSpeed * _DeltaTime);

	if (TrapAnimationTime < 0.f)
	{
		switch (Info->MyType)
		{
		case ECharacterType::Bazzi:
			Renderer->ChangeAnimation("Bazzi_Trap_Last");
			break;
		case ECharacterType::Dao:
			Renderer->ChangeAnimation("Dao_Trap_Last");
			break;
		default:
			break;
		}
	}

	// 예시 인터페이스
	//APlayer* Other = IsOtherPlayer(GetActorLocation());
	//if (nullptr != Other)	// 이 위치에 다른 플레이어가 있다면
	//{
	//	if (Other->Info->Team == Info->Team)	// 같은 팀
	//	{
	//		State.ChangeState("Rescue");
	//		return;
	//	}
	//	else									// 다른 팀
	//	{
	//		State.ChangeState("Die");
	//		return;
	//	}
	//}

	// Trap 이후 DieTime 초과 시 Die 상태로 변경
	if (TrapToDieTime < 0.f)
	{
		Renderer->SetPosition(FVector::Zero);
		State.ChangeState("Die");
		return;
	}
}

void APlayer::RescueStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Rescue"));
}

void APlayer::Rescue(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::DieStart()
{
	Renderer->ChangeAnimation(GetAnimationName("Die"));

	DieAnimationChange = false;
	DieAniTwinkleActive = true;
	DieTwinkleTime = 0.1f;
	DieAnimationTime = 2.f;
}

void APlayer::Die(float _DeltaTime)
{
	if (false == DieAnimationChange && UEngineString::ToUpper(GetAnimationName("Die")) == Renderer->GetCurAniName() && true == Renderer->IsCurAnimationEnd())
	{
		DieAnimationChange = true;
		
		switch (Info->MyType)
		{
		case ECharacterType::Bazzi:
			Renderer->ChangeAnimation("Bazzi_Die_Last");
			break;
		case ECharacterType::Dao:
			Renderer->ChangeAnimation("Dao_Die_Last");
			break;
		default:
			break;
		}
	}

	if (true == DieAnimationChange)
	{
		DieAnimationTime -= _DeltaTime;
		DieTwinkleTime -= _DeltaTime;

		if (DieTwinkleTime < 0.f)
		{
			Renderer->SetActive(DieAniTwinkleActive);
			DieAniTwinkleActive = !DieAniTwinkleActive;
			DieTwinkleTime = 0.1f;
		}

		if (DieAnimationTime < 0.f)
		{
			State.ChangeState("RealDie");
			return;
		}
	}

}

void APlayer::RealDieStart()
{
	// 진짜 죽음 처리
	Shadow->SetActive(false);
	Renderer->SetActive(false);
}

void APlayer::RealDie(float _DeltaTime)
{

}