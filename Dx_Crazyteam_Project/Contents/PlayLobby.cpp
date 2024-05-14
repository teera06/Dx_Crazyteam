#include "PreCompile.h"
#include "PlayLobby.h"

#include "EngineCore/Image.h"

APlayLobby::APlayLobby()
{
	Collision0 = CreateDefaultSubObject<UCollision>("Collision");
	Collision0->SetScale({ 63.f,42.f });
	Collision0->SetPosition({ 122.0f,162.0f });
	Collision0->SetCollisionGroup(ECollisionOrder::Player);
	Collision0->SetCollisionType(ECollisionType::Rect);
}

APlayLobby::~APlayLobby()
{
}

void APlayLobby::BeginPlay()
{
	Super::BeginPlay();
	InputOn();

	PlayLobbyUI = CreateWidget<UImage>(GetWorld(), "PlayLobbyUI");
	PlayLobbyUI->AddToViewPort(10);
	PlayLobbyUI->SetSprite("Waiting.png");
	PlayLobbyUI->SetScale({ 800, 600 });
	PlayLobbyUI->SetActive(true);

	Random = CreateWidget<UImage>(GetWorld(), "Q");
	Random->AddToViewPort(11);
	Random->SetSprite("CharatorSelect_Button_Random_Normal.bmp");
	Random->SetScale({ 63.f,42.f });
	Random->SetPosition({ 122.0f,162.0f });
	Random->SetActive(true);



}

void APlayLobby::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	PlayLobbyUI->SetActive(true);


	//Collision0->CollisionEnter(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
	//	{
	//		Q->SetSprite("CharatorSelect_Button_Random_Hover.bmp");
	//	}
	//);
	//Collision0->CollisionExit(ECollisionOrder::Mouse, [=](std::shared_ptr<UCollision> _Collison)
	//	{
	//		Q->SetSprite("CharatorSelect_Button_Random_Hover.bmp");
	//	}
	//);
}

void APlayLobby::SetIsActive(bool _Active)
{
	PlayLobbyUI->SetActive(_Active);
}