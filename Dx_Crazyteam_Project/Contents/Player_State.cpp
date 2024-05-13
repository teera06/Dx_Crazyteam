#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	//여기서 랜더러 CreateAnimation 등 해줘야함.

	InputOn();


	// 스테이트 만들고
	State.CreateState("Die");
	State.CreateState("Idle");
	State.CreateState("Move");
	State.CreateState("Attack");

	

	State.SetStartFunction("Idle", [this]()
		{
			
		});

	State.SetUpdateFunction("Idle", [=](float _Delta)
		{

		});

	// 체인지
	State.ChangeState("Idle");
}


void  APlayer::Idle()
{

}

