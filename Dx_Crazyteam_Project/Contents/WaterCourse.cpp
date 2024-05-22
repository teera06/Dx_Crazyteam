#include "PreCompile.h"
#include "WaterCourse.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "BaseMap.h"
#include "CAGameMode.h"
#include "Player.h"
#include "WaterBomb.h"
#include "Packets.h"
#include "Game_Core.h"
#include "Bush.h"

int AWaterCourse::WaterCourseToken = 0;
bool AWaterCourse::SetToken = false;

AWaterCourse::AWaterCourse()
{

}

AWaterCourse::~AWaterCourse()
{
}



void AWaterCourse::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
	CreateAnimation();

	Renderer->SetAutoSize(1.0f, true);
	//Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetActive(false);

	SetType(EMapObjectType::Water);
}

void AWaterCourse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);

	if (true == CreateStart)
	{
		CreateWaterStream(_DeltaTime);
	}
}

void AWaterCourse::StateInit()
{
	State.CreateState("None");

	State.CreateState("CreateCenter"); // 중간 물줄기.
	State.CreateState("CreateStream"); // 물 줄기.
	State.CreateState("CreateEndStem");// 물 줄기 끝.

	State.CreateState("Delete"); // 사라짐.

	State.SetStartFunction("None", std::bind(&AWaterCourse::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&AWaterCourse::NoneTick, this, std::placeholders::_1));


	State.SetFunction("CreateCenter",
		std::bind(&AWaterCourse::CreateCenterBegin, this),
		std::bind(&AWaterCourse::CreateCenterTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::CreateCenterExit, this));
	State.SetFunction("CreateStream",
		std::bind(&AWaterCourse::CreateStreamBegin, this),
		std::bind(&AWaterCourse::CreateStreamTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::CreateStreamExit, this));
	State.SetFunction("CreateEndStem",
		std::bind(&AWaterCourse::CreateEndStemBegin, this),
		std::bind(&AWaterCourse::CreateEndStemTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::CreateEndStemExit, this));

	State.SetFunction("Delete",
		std::bind(&AWaterCourse::DeleteBegin, this),
		std::bind(&AWaterCourse::DeleteTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::DeleteExit, this));

	State.ChangeState("None");
}


void AWaterCourse::CreateAnimation()
{
	// 물 줄기 센터
	Renderer->CreateAnimation("Water_Center", "Center11.png", 0.0625f, true, 0, 1);
	Renderer->CreateAnimation("Water_Center_End", "Center11.png", 0.0625f, false);

	{
		// 물줄기 뻗어 나갈 때 사용할 애니메이션
		Renderer->CreateAnimation("CreateUp", "up12.png", 0.0625f, true, 0, 0);
		Renderer->CreateAnimation("CreateDown", "down12.png", 0.0625f, true, 0, 0);
		Renderer->CreateAnimation("CreateLeft", "left12.png", 0.0625f, true, 0, 0);
		Renderer->CreateAnimation("CreateRight", "right12.png", 0.0625f, true, 0, 0);
	}

	{
		// 물 끝. -> Tick에서 사용할 애니메이션.
		Renderer->CreateAnimation("EndStemUp", "up12.png", 0.0625f, true, 0, 1);
		Renderer->CreateAnimation("EndStemDown", "down12.png", 0.0625f, true, 0, 1);
		Renderer->CreateAnimation("EndStemLeft", "left12.png", 0.0625f, true, 0, 1);
		Renderer->CreateAnimation("EndStemRight", "right12.png", 0.0625f, true, 0, 1);

		// 물 줄기 중간 -> Tick에서 사용할 애니메이션.
		Renderer->CreateAnimation("StreamUp", "up22.png", 0.0625f, true, 0, 2);
		Renderer->CreateAnimation("StreamDown", "down22.png", 0.0625f, true, 0, 2);
		Renderer->CreateAnimation("StreamLeft", "left22.png", 0.0625f, true, 0, 2);
		Renderer->CreateAnimation("StreamRight", "right22.png", 0.0625f, true, 0, 2);
	}

	{
		// 물 끝 사라짐.
		Renderer->CreateAnimation("D_EndStemUp", "up12.png", 0.0625f, true, 1, 10);
		Renderer->CreateAnimation("D_EndStemDown", "down12.png", 0.0625f, true, 1, 10);
		Renderer->CreateAnimation("D_EndStemLeft", "left12.png", 0.0625f, true, 1, 10);
		Renderer->CreateAnimation("D_EndStemRight", "right12.png", 0.0625f, true, 1, 10);

		// 물 줄기 사라짐.
		Renderer->CreateAnimation("D_StreamUp", "up22.png", 0.0625f, true, 1, 10);
		Renderer->CreateAnimation("D_StreamDown", "down22.png", 0.0625f, true, 1, 10);
		Renderer->CreateAnimation("D_StreamLeft", "left22.png", 0.0625f, true, 1, 10);
		Renderer->CreateAnimation("D_StreamRight", "right22.png", 0.0625f, true, 1, 10);
	}

	Renderer->ChangeAnimation("Water_Center");
}

#pragma region None
void AWaterCourse::NoneBegin()
{
}

void AWaterCourse::NoneTick(float _DeltaTime)
{
}
#pragma endregion

#pragma region Center
void AWaterCourse::CreateCenterBegin()
{
	CenterLifeTime = 0.0f;
	CreateStart = true; // 물줄기 만들어라.
	Renderer->ChangeAnimation("Water_Center");
	PreAniName = "Water_Center";
	Renderer->SetActive(true);
}
void AWaterCourse::CreateCenterTick(float _DeltaTime)
{
	CenterLifeTime += _DeltaTime;
	if (LifeTime <= CenterLifeTime)
	{
		State.ChangeState("Delete");
		return;
	}

	if (false == b_BombCountUpdateOne)
	{
		std::shared_ptr<APlayer> TestPlayer = GetGameMode()->GetPlayer();
		int WBCount = TestPlayer->GetWBCount();
		WBCount += 1;
		TestPlayer->SetWBCount(WBCount);
		b_BombCountUpdateOne = true;
	}
}
void AWaterCourse::CreateCenterExit()
{
	CenterLifeTime = 0.0f;
}
#pragma endregion

#pragma region CreateStream // 물줄기
void AWaterCourse::CreateStreamBegin()
{
	switch (WaterCourseDir)
	{
	case EEngineDir::Up:
	{
		Renderer->ChangeAnimation("StreamUp");
		PreAniName = "StreamUp";
		break;
	}
	case EEngineDir::Down :
	{
		Renderer->ChangeAnimation("StreamDown");
		PreAniName = "StreamDown";
		break;
	}
	case EEngineDir::Left:
	{
		Renderer->ChangeAnimation("StreamLeft");
		PreAniName = "StreamLeft";
		break;
	}
	case EEngineDir::Right:
	{
		Renderer->ChangeAnimation("StreamRight");
		PreAniName = "StreamRight";
		break;
	}
	default :
		break;
	}

	Renderer->SetActive(true);
}

void AWaterCourse::CreateStreamTick(float _DeltaTime)
{
	CenterLifeTime += _DeltaTime;

	if (LifeTime <= CenterLifeTime)
	{
		State.ChangeState("Delete");
		return;
	}

	// 플레이어 닿을 때.

}
void AWaterCourse::CreateStreamExit()
{
	CenterLifeTime = 0.0f;
}
#pragma endregion

#pragma region CreateEndStem  TODO
void AWaterCourse::CreateEndStemBegin()
{
	switch (WaterCourseDir)
	{
	case EEngineDir::Up:
	{
		Renderer->ChangeAnimation("EndStemUp");
		PreAniName = "EndStemUp";
		break;
	}
	case EEngineDir::Down :
	{
		Renderer->ChangeAnimation("EndStemDown");
		PreAniName = "EndStemDown";
		break;
	}
	case EEngineDir::Left:
	{
		Renderer->ChangeAnimation("EndStemLeft");
		PreAniName = "EndStemLeft";
		break;
	}
	case EEngineDir::Right:
	{
		Renderer->ChangeAnimation("EndStemRight");
		PreAniName = "EndStemRight";
		break;
	}
	default :
		break;
	}

	Renderer->SetActive(true);
}
void AWaterCourse::CreateEndStemTick(float _DeltaTime)
{
	CenterLifeTime += _DeltaTime;

	if (LifeTime <= CenterLifeTime)
	{
		State.ChangeState("Delete");
		return;
	}
}
void AWaterCourse::CreateEndStemExit()
{
	CenterLifeTime = 0.0f;
}
#pragma endregion



#pragma region Delete
void AWaterCourse::DeleteBegin()
{
	//WaterCourseRender->ChangeAnimation(PreAniName);

	if (PreAniName == "Water_Center")
	{
		Renderer->ChangeAnimation("Water_Center_End");
		PreAniName = "Water_Center_End";
	}
	else if (PreAniName == "EndStemUp")
	{
		Renderer->ChangeAnimation("D_EndStemUp");
		PreAniName = "D_EndStemUp";
	}
	else if (PreAniName == "EndStemDown")
	{
		Renderer->ChangeAnimation("D_EndStemDown");
		PreAniName = "D_EndStemDown";
	}
	else if (PreAniName == "EndStemLeft")
	{
		Renderer->ChangeAnimation("D_EndStemLeft");
		PreAniName = "D_EndStemLeft";
	}
	else if (PreAniName == "EndStemRight")
	{
		Renderer->ChangeAnimation("D_EndStemRight");
		PreAniName = "D_EndStemRight";
	}
	else if (PreAniName == "StreamUp")
	{
		Renderer->ChangeAnimation("D_StreamUp");
		PreAniName = "D_StreamUp";
	}
	else if (PreAniName == "StreamDown")
	{
		Renderer->ChangeAnimation("D_StreamDown");
		PreAniName = "D_StreamDown";
	}
	else if (PreAniName == "StreamLeft")
	{
		Renderer->ChangeAnimation("D_StreamLeft");
		PreAniName = "D_StreamLeft";
	}
	else if (PreAniName == "StreamRight")
	{
		Renderer->ChangeAnimation("D_StreamRight");
		PreAniName = "D_StreamRight";
	}
}

void AWaterCourse::DeleteTick(float _DeltaTime)
{
	// Animation Final Frame callback
	Renderer->SetLastFrameCallback(PreAniName, [=]()
		{
			Renderer->SetActive(false);
			GetGameMode()->GetCurMap()->DestroyMapObject(GetCurPos().y, GetCurPos().x);
		}
	);
}

void AWaterCourse::DeleteExit()
{
}
#pragma endregion

// 터지면 들어옴.
void AWaterCourse::CreateWaterStream(float _DeltaTime)
{
	CreateDeltaTime += _DeltaTime;

	POINT WaterBombPoint = GetCurPos();

	int WaterPower = GetGameMode()->GetPlayer()->GetPlayerInfo()->WBPower;
	size_t GetWaterPower_t = static_cast<size_t>(WaterPower);

	if (WaterPower != DefaultPowerValue)
	{
		{
			if (0 <= GetCurPos().y - DefaultPowerValue && false == UpEnd)
			{
				// 만들어 질 곳에 뭐가 있음?
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y - DefaultPowerValue, GetCurPos().x);

				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
						UpEnd = true;
					}
					else if (type == EMapObjectType::Item)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							UpEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}
				
				if (NextMapObject == nullptr && UpEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, false, EEngineDir::Up));
				}
				else if (EMapObjectType::Item == NextMapObject->GetType() && false == UpEnd)
				{
					// 아이템이 있던 곳에 아이템이 지워졌으니 물줄기 생성.
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, false, EEngineDir::Up));
				}
				else if (EMapObjectType::Bush == NextMapObject->GetType() && false == UpEnd)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, false, EEngineDir::Up));
				}
			}

			if (12 >= GetCurPos().y + DefaultPowerValue && false == DownEnd)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y + DefaultPowerValue, GetCurPos().x);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
						DownEnd = true;
					}
					else if (type == EMapObjectType::Item)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							DownEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}

				if (NextMapObject == nullptr && DownEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, false, EEngineDir::Down));
					
				}
				else if (EMapObjectType::Item == NextMapObject->GetType() && false == DownEnd)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, false, EEngineDir::Down));
					
				}
				else if (EMapObjectType::Bush == NextMapObject->GetType() && false == DownEnd)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, false, EEngineDir::Down));
				}
			}

			if (0 <= GetCurPos().x - DefaultPowerValue && false == LeftEnd)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x - DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
						LeftEnd = true;
					}
					else if (type == EMapObjectType::Item)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							LeftEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}

				if (NextMapObject == nullptr && LeftEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, false, EEngineDir::Left));
					
				}
				else if (EMapObjectType::Item == NextMapObject->GetType() && false == LeftEnd)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, false, EEngineDir::Left));
					
				}
				else if (EMapObjectType::Bush == NextMapObject->GetType() && false == LeftEnd)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, false, EEngineDir::Left));
					
				}
			}

			if (14 >= GetCurPos().x + DefaultPowerValue && false == RightEnd)
			{
				POINT x = GetCurPos();
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x + DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
						RightEnd = true;
					}
					else if (type == EMapObjectType::Item)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							RightEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}

				if (NextMapObject == nullptr && RightEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, false, EEngineDir::Right));
				}
				else if (EMapObjectType::Item == NextMapObject->GetType() && false == RightEnd)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, false, EEngineDir::Right));
				}
				else if (EMapObjectType::Bush == NextMapObject->GetType() && false == RightEnd)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, false, EEngineDir::Right));
				}
			}
		}
		DefaultPowerValue++;
	}
	else if(WaterPower == DefaultPowerValue)
	{
		{
			if (0 <= GetCurPos().y - DefaultPowerValue)
			{
				// 만들어 질 곳에 뭐가 있음?
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y - DefaultPowerValue, GetCurPos().x);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block && false == UpEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::Item && false == UpEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon && false == UpEnd)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush && false == UpEnd)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							UpEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}

				if (NextMapObject == nullptr && UpEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, true, EEngineDir::Up));
					
				}
				else if (NextMapObject != nullptr && EMapObjectType::Item == NextMapObject->GetType() && UpEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, true, EEngineDir::Up));
					
				}
				else if (NextMapObject != nullptr && EMapObjectType::Bush == NextMapObject->GetType() && UpEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, true, EEngineDir::Up));
					
				}
			}

			if (12 >= GetCurPos().y + DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y + DefaultPowerValue, GetCurPos().x);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block && false == DownEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::Item && false == DownEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon && false == DownEnd)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush && false == DownEnd)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							DownEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}

				if (NextMapObject == nullptr && DownEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, true, EEngineDir::Down));
					
				}
				else if (NextMapObject != nullptr && EMapObjectType::Item == NextMapObject->GetType() && DownEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, true, EEngineDir::Down));
					
				}
				else if (NextMapObject != nullptr && EMapObjectType::Bush == NextMapObject->GetType() && DownEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, true, EEngineDir::Down));
					
				}
			}

			if (0 <= GetCurPos().x - DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x - DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block && false == LeftEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::Item && false == LeftEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon && false == LeftEnd)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush && false == LeftEnd)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							LeftEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}

				if (NextMapObject == nullptr && LeftEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, true, EEngineDir::Left));
					
				}
				else if (NextMapObject != nullptr && EMapObjectType::Item == NextMapObject->GetType() && LeftEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, true, EEngineDir::Left));
					
				}
				else if (NextMapObject != nullptr && EMapObjectType::Bush == NextMapObject->GetType() && LeftEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, true, EEngineDir::Left));
					
				}
			}

			if (14 >= GetCurPos().x + DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x + DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block && false == RightEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::Item && false == RightEnd)
					{
						NextMapObject->WaterInteract();
					}
					else if (type == EMapObjectType::WaterBalloon && false == RightEnd)
					{
						AWaterBomb* NextBomb = dynamic_cast<AWaterBomb*>(NextMapObject.get());
						NextBomb->SetWaterToBomg(true);
					}
					else if (type == EMapObjectType::Bush && false == RightEnd)
					{
						// 부쉬안에 뭐가 있음?
						std::shared_ptr<ABush> IsOn = std::dynamic_pointer_cast<ABush>(NextMapObject);

						// 부쉬 안에 뭔가 있음.
						if (nullptr != IsOn->GetPossessBlock())
						{
							NextMapObject->WaterInteract();
							IsOn->GetPossessBlock()->WaterInteract();

							// 물줄기가 안나가도록 막아야 한다.
							RightEnd = true;
						}
						else
						{
							// 부쉬 지움.
							NextMapObject->WaterInteract();
						}
					}
				}


				if (NextMapObject == nullptr && RightEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, true, EEngineDir::Right));
				}
				else if (NextMapObject != nullptr && EMapObjectType::Item == NextMapObject->GetType() && RightEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, true, EEngineDir::Right));
				}
				else if (NextMapObject != nullptr && EMapObjectType::Bush == NextMapObject->GetType() && RightEnd == false)
				{
					std::shared_ptr<AWaterCourse> WaterCourse = dynamic_pointer_cast<AWaterCourse>(GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, true, EEngineDir::Right));
				}
			}
		}

		CreateStart = false; // Tick Control
	}

	

	//NextMapObject->WaterInteract();
}