#include "PreCompile.h"
#include <EngineCore/Image.h>
#include "OtherLobbyPlayer.h"
#include "Game_Core.h"
#include "Packets.h"

AOtherLobbyPlayer::AOtherLobbyPlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);
}

AOtherLobbyPlayer::~AOtherLobbyPlayer()
{
}

void AOtherLobbyPlayer::SetRenderer(std::string_view _SpriteName, int _Index)
{
	ImageRenderer->SetSprite(_SpriteName);
}

void AOtherLobbyPlayer::SetPosition(int _SessionToken)
{
	ImageRenderer->SetPosition(FVector(static_cast<float>(-335 + _SessionToken * 105), 160.0f, 100.0f));
}

void AOtherLobbyPlayer::BeginPlay()
{
	ImageRenderer = CreateWidget<UImage>(GetWorld(), "Room1");
	ImageRenderer->SetAutoSize(1.2f, true);
	ImageRenderer->SetPosition(FVector(0.f, 0.f));
	ImageRenderer->SetActive(true);
	ImageRenderer->AddToViewPort(15);
	Super::BeginPlay();
}

void AOtherLobbyPlayer::Tick(float _DeltaTime)
{
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
			
		std::shared_ptr<ULobbyPlayerUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<ULobbyPlayerUpdatePacket>(Protocol);

		std::string SpriteNames = UpdatePacket->SpriteName;
		int Index = UpdatePacket->SpriteIndex;
		SetRenderer(SpriteNames, Index);
		const int Token = 110000;
		SetPosition(UpdatePacket->GetObjectToken()- Token);

	} while (nullptr != Protocol);
}
