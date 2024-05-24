#include "PreCompile.h"
#include "OtherPlayer.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "Game_Core.h"
#include "Packets.h"
#include <EngineCore/TextWidget.h>
#include "stringHelper.h"
#include <EngineCore/Image.h>

AOtherPlayer::AOtherPlayer() 
{

	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetAutoSize(0.05f, true);
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(5);
	SetActorScale3D(FVector(20, 20, 1));
}

AOtherPlayer::~AOtherPlayer() 
{
}

void AOtherPlayer::BeginPlay()
{
	AActor::BeginPlay();

	PlayerNameUI = CreateWidget<UTextWidget>(GetWorld(), "PlayerNameTag");
	PlayerNameUI->SetFont("굴림");
	PlayerNameUI->SetText("");
	//PlayerNameUI->SetText(stringHelper::GetPlayerName());
	PlayerNameUI->SetPosition(GetActorLocation() - ConstValue::CameraPos + FVector(0, 70));
	PlayerNameUI->SetScale(15.0f);
	PlayerNameUI->SetColor(Color8Bit::Black);
	PlayerNameUI->SetOrder(1);
	PlayerNameUI->AddToViewPort(11);

	NameListUI = CreateWidget<UTextWidget>(GetWorld(), "PlayerNameList");
	NameListUI->SetFont("굴림");
	NameListUI->SetText("");
	NameListUI->SetPosition(FVector::Zero);
	NameListUI->SetScale(15.0f);
	NameListUI->SetColor(Color8Bit::Black);
	NameListUI->SetOrder(1);
	NameListUI->AddToViewPort(11);

	PlayerListUI = CreateWidget<UImage>(GetWorld(), "PlayerUIList");
	PlayerListUI->AddToViewPort(11);
	//PlayerListUI->SetSprite(""); << 이거대신 애니메이션 해야함
	//PlayerListUI->SetScale({ 281.f, 80.f });
	//PlayerListUI->SetPosition({ 230.0f,237.0f });
	PlayerListUI->SetActive(true);
}

void AOtherPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
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

			if (static_cast<int>(EObjectType::Player) != ActorUpdatePacket->ObjectType)
			{
				break;
			}

			SetActorLocation(ActorUpdatePacket->Pos);

			TeamType = static_cast<ETeamType>(ActorUpdatePacket->TeamType);
			if (TeamType == ETeamType::ATeam)
			{
				PlayerNameUI->SetColor(Color8Bit::Red);
			}
			else if (TeamType == ETeamType::BTeam)
			{
				PlayerNameUI->SetColor(Color8Bit::Blue);
			}

			CharacterType = static_cast<ECharacterType>(ActorUpdatePacket->CharacterType);

			std::string SpriteNames = ActorUpdatePacket->SpriteName;
			std::string UserName = ActorUpdatePacket->UserName;
			NameListUI->SetText(UserName);
			int AnimationInFO = ActorUpdatePacket->AnimationInfo;

			if (SpriteNames != "")
			{
				Renderer->SetActive(ActorUpdatePacket->RendererIsActive);
				Renderer->SetSprite(SpriteNames, AnimationInFO);
				Renderer->SetAlpha(ActorUpdatePacket->SpriteAlpha);
				Renderer->SetPosition(ActorUpdatePacket->RendererPos);
			}

			IsOPDestroy = ActorUpdatePacket->IsDestroy;
			if (true == IsOPDestroy)
			{
				PlayerNameUI->SetActive(false);
			}
			else
			{
				PlayerNameUI->SetText(UserName);
				PlayerNameUI->SetPosition(GetActorLocation() - ConstValue::CameraPos + FVector(0, 70));
			}

			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);

}

void AOtherPlayer::IdleStart()
{
}

void AOtherPlayer::Idle(float _DeltaTime)
{
}

void AOtherPlayer::MoveStart()
{
}

void AOtherPlayer::Move(float _DeltaTime)
{
}
