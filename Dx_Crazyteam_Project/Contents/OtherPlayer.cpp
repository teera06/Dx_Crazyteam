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
	NameListUI->SetFlag(FW1_LEFT);
	NameListUI->SetPosition(FVector::Zero);
	NameListUI->SetScale(15.0f);
	NameListUI->SetColor(Color8Bit::White);
	NameListUI->SetOrder(1);
	NameListUI->AddToViewPort(11);

	PlayerListUI = CreateWidget<UImage>(GetWorld(), "PlayerUIList");
	PlayerListUI->AddToViewPort(15);
	PlayerListUI->SetSprite("Play_Portrait_Bazzi_Normal_R.png");
	PlayerListUI->SetAutoSize(1.0f, true);
	PlayerListUI->SetPosition({ 0, 0 });
	PlayerListUI->CreateAnimation("Bazzi_R_Nor", "Play_Portrait_Bazzi_Normal_R.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Bazzi_B_Nor", "Play_Portrait_Bazzi_Normal_B.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Bazzi_R_Cry", "Play_Portrait_Bazzi_Lose_R.png", 0.1f, true, 0, 3);
	PlayerListUI->CreateAnimation("Bazzi_B_Cry", "Play_Portrait_Bazzi_Lose_B.png", 0.1f, true, 0, 3);

	PlayerListUI->CreateAnimation("Dao_R_Nor", "Play_Portrait_Dao_Normal_R.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Dao_B_Nor", "Play_Portrait_Dao_Normal_B.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Dao_R_Cry", "Play_Portrait_Dao_Lose_R.png", 0.1f, true, 0, 3);
	PlayerListUI->CreateAnimation("Dao_B_Cry", "Play_Portrait_Dao_Lose_B.png", 0.1f, true, 0, 3);

	PlayerListUI->CreateAnimation("Marid_R_Nor", "Play_Portrait_Marid_Normal_R.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Marid_B_Nor", "Play_Portrait_Marid_Normal_B.png", 0.2f, true, 0, 1);
	PlayerListUI->CreateAnimation("Marid_R_Cry", "Play_Portrait_Marid_Lose_R.png", 0.1f, true, 0, 3);
	PlayerListUI->CreateAnimation("Marid_B_Cry", "Play_Portrait_Marid_Lose_B.png", 0.1f, true, 0, 3);
	PlayerListUI->ChangeAnimation("Bazzi_R_Nor");
	PlayerListUI->SetActive(true);
}

std::string AOtherPlayer::GetAnimationName(std::string_view _name)
{
	std::string AniName = "";

	switch (CharacterType)
	{
	case ECharacterType::Bazzi:
		AniName = "Bazzi_";
		break;
	case ECharacterType::Dao:
		AniName = "Dao_";
		break;
	case ECharacterType::Marid:
		AniName = "Marid_";
		break;
	default:
		break;
	}

	switch (TeamType)
	{
	case ETeamType::None:
		break;
	case ETeamType::ATeam:
		AniName += "R_";
		break;
	case ETeamType::BTeam:
		AniName += "B_";
		break;
	default:
		break;
	}

	AniName += _name.data();

	return AniName;
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
			if(false == TempBool2)
			{
				PlayerListUI->ChangeAnimation(GetAnimationName("Nor"));
				TempBool2 = true;
			}


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

			{
				SessionToken = ActorUpdatePacket->GetSessionToken();
			}

			break;
		}
		default:
			break;
		}
	} while (nullptr != Protocol);

	FVector Pos = FVector(280.0f, 180 - static_cast<float>((SessionToken * 43)), 100.0f);
	PlayerListUI->SetPosition(Pos);
	NameListUI->SetPosition(Pos + FVector(21,0,0));
	if (TempBool != IsOPDestroy)
	{
		TempBool = IsOPDestroy;
		PlayerListUI->ChangeAnimation(GetAnimationName("Cry"));
	}
	
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
