#include "PreCompile.h"

#include "OtherLobbyPlayer.h"

AOtherLobbyPlayer::AOtherLobbyPlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("RendererRoot");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetAutoSize(0.05f, true);
	Renderer->SetOrder(5);
	SetActorScale3D(FVector(20, 20, 1));


	ImageRenderer = CreateWidget<UImage>(GetWorld(), "Room1");
	//Room1->CreateAnimation("UnHover", "Room_0.png", 0.1f, false, 0, 0);
	//Room1->CreateAnimation("Hover", "Room_1.png", 0.1f, false, 0, 0);
	//Room1->CreateAnimation("Down", "Room_2.png", 0.1f, false, 0, 0);
	//Room1->CreateAnimation("Up", "RoomX_0.png", 0.1f, false, 0, 0);
	//Room1->CreateAnimation("XUnHover", "RoomX_0.png", 0.1f, false, 0, 0);
	//Room1->CreateAnimation("XHover", "RoomX_1.png", 0.1f, false, 0, 0);
	//Room1->CreateAnimation("XDown", "RoomX_2.png", 0.1f, false, 0, 0);
	//Room1->CreateAnimation("XUp", "Room_0.png", 0.1f, false, 0, 0);
	//Room1->AddToViewPort(12);
	//Room1->SetSprite("Room_0.png");
	//ImageRenderer->SetAutoSize(1.0f, true);
	//ImageRenderer->SetPosition(FVector(-218.f, 157.f));
	//ImageRenderer->SetActive(true);


}

AOtherLobbyPlayer::~AOtherLobbyPlayer()
{
}

void AOtherLobbyPlayer::SetRenderer(std::string_view _SpriteName, int _Index)
{
	Renderer->SetSprite(_SpriteName, _Index);
}

void AOtherLobbyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AOtherLobbyPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
