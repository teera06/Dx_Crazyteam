#include "PreCompile.h"

#include "ServerTestOtherPlayer.h"
#include "Game_Core.h"
#include "Packets.h"
#include "CAGameMode.h"
#include "BaseMap.h"

AServerTestOtherPlayer::AServerTestOtherPlayer()
	:APlayer()
{
}

AServerTestOtherPlayer::~AServerTestOtherPlayer()
{
}

void AServerTestOtherPlayer::BeginPlay()
{
	Super::BeginPlay();

	OffIsSendPacket();
}

void AServerTestOtherPlayer::Tick(float _DeltaTime)
{
	InputOff();

	Super::Tick(_DeltaTime);

	if (nullptr == UGame_Core::Net)
	{
		MsgBoxAssert("네트워크 연결이 안된상태에서 아더플레어를 만들었습니다.");
	}

	std::shared_ptr<UEngineProtocol> Protocol = nullptr;

	do
	{
		Protocol = PopProtocol();
		if (nullptr == Protocol)
		{
			break;
		}

		EContentPacket PacketType = Protocol->GetPacketType<EContentPacket>();

		switch (PacketType)
		{
		case ActorUpdatePacket:
		{
			std::shared_ptr<UActorUpdatePacket> ActorUpdatePacket = std::dynamic_pointer_cast<UActorUpdatePacket>(Protocol);

			SetActorLocation(ActorUpdatePacket->Pos);

			GetGameMode()->GetCurMap()->IsMove(ActorUpdatePacket->Pos);

			break;
		}
		default:
			break;
		}

	} while (nullptr != Protocol);
}