#include "PreCompile.h"
#include "WaterCourse.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "BaseMap.h"
#include "CAGameMode.h"
#include "Player.h"

AWaterCourse::AWaterCourse()
{
	WaterCourseRender = CreateDefaultSubObject<USpriteRenderer>("Render");
	WaterCourseRender->SetupAttachment(Root);
}

AWaterCourse::~AWaterCourse()
{
}

void AWaterCourse::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
	CreateAnimation();

	WaterCourseRender->SetAutoSize(1.0f, true);
	WaterCourseRender->SetOrder(ERenderOrder::Player);
	WaterCourseRender->SetActive(false);

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
	WaterCourseRender->CreateAnimation("Water_Center", "Center11.png", 0.0625f, true, 0, 1);
	WaterCourseRender->CreateAnimation("Water_Center_End", "Center11.png", 0.0625f, false);

	{
		// 물줄기 뻗어 나갈 때 사용할 애니메이션
		WaterCourseRender->CreateAnimation("CreateUp", "up12.png", 0.0625f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateDown", "down12.png", 0.0625f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateLeft", "left12.png", 0.0625f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateRight", "right12.png", 0.0625f, true, 0, 0);
	}

	{
		// 물 끝. -> Tick에서 사용할 애니메이션.
		WaterCourseRender->CreateAnimation("EndStemUp", "up12.png", 0.0625f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemDown", "down12.png", 0.0625f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemLeft", "left12.png", 0.0625f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemRight", "right12.png", 0.0625f, true, 0, 1);

		// 물 줄기 중간 -> Tick에서 사용할 애니메이션.
		WaterCourseRender->CreateAnimation("StreamUp", "up22.png", 0.0625f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamDown", "down22.png", 0.0625f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamLeft", "left22.png", 0.0625f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamRight", "right22.png", 0.0625f, true, 0, 2);
	}

	{
		// 물 끝 사라짐.
		WaterCourseRender->CreateAnimation("D_EndStemUp", "up12.png", 0.0625f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_EndStemDown", "down12.png", 0.0625f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_EndStemLeft", "left12.png", 0.0625f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_EndStemRight", "right12.png", 0.0625f, true, 1, 10);

		// 물 줄기 사라짐.
		WaterCourseRender->CreateAnimation("D_StreamUp", "up22.png", 0.0625f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_StreamDown", "down22.png", 0.0625f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_StreamLeft", "left22.png", 0.0625f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_StreamRight", "right22.png", 0.0625f, true, 1, 10);
	}

	WaterCourseRender->ChangeAnimation("Water_Center");
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
	WaterCourseRender->ChangeAnimation("Water_Center");
	PreAniName = "Water_Center";
	WaterCourseRender->SetActive(true);
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
		ACAGameMode* TestGameMode = GetGameMode();
		std::shared_ptr<APlayer> TestPlayer = TestGameMode->GetPlayer();
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
		WaterCourseRender->ChangeAnimation("StreamUp");
		PreAniName = "StreamUp";
		break;
	}
	case EEngineDir::Down :
	{
		WaterCourseRender->ChangeAnimation("StreamDown");
		PreAniName = "StreamDown";
		break;
	}
	case EEngineDir::Left:
	{
		WaterCourseRender->ChangeAnimation("StreamLeft");
		PreAniName = "StreamLeft";
		break;
	}
	case EEngineDir::Right:
	{
		WaterCourseRender->ChangeAnimation("StreamRight");
		PreAniName = "StreamRight";
		break;
	}
	default :
		break;
	}

	WaterCourseRender->SetActive(true);
}

void AWaterCourse::CreateStreamTick(float _DeltaTime)
{
	CenterLifeTime += _DeltaTime;

	if (2.0f <= CenterLifeTime)
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
		WaterCourseRender->ChangeAnimation("EndStemUp");
		PreAniName = "EndStemUp";
		break;
	}
	case EEngineDir::Down :
	{
		WaterCourseRender->ChangeAnimation("EndStemDown");
		PreAniName = "EndStemDown";
		break;
	}
	case EEngineDir::Left:
	{
		WaterCourseRender->ChangeAnimation("EndStemLeft");
		PreAniName = "EndStemLeft";
		break;
	}
	case EEngineDir::Right:
	{
		WaterCourseRender->ChangeAnimation("EndStemRight");
		PreAniName = "EndStemRight";
		break;
	}
	default :
		break;
	}

	WaterCourseRender->SetActive(true);
}
void AWaterCourse::CreateEndStemTick(float _DeltaTime)
{
	CenterLifeTime += _DeltaTime;

	if (2.0f <= CenterLifeTime)
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
		WaterCourseRender->ChangeAnimation("Water_Center_End");
		PreAniName = "Water_Center_End";
	}
	else if (PreAniName == "EndStemUp")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemUp");
		PreAniName = "D_EndStemUp";
	}
	else if (PreAniName == "EndStemDown")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemDown");
		PreAniName = "D_EndStemDown";
	}
	else if (PreAniName == "EndStemLeft")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemLeft");
		PreAniName = "D_EndStemLeft";
	}
	else if (PreAniName == "EndStemRight")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemRight");
		PreAniName = "D_EndStemRight";
	}
	else if (PreAniName == "StreamUp")
	{
		WaterCourseRender->ChangeAnimation("D_StreamUp");
		PreAniName = "D_StreamUp";
	}
	else if (PreAniName == "StreamDown")
	{
		WaterCourseRender->ChangeAnimation("D_StreamDown");
		PreAniName = "D_StreamDown";
	}
	else if (PreAniName == "StreamLeft")
	{
		WaterCourseRender->ChangeAnimation("D_StreamLeft");
		PreAniName = "D_StreamLeft";
	}
	else if (PreAniName == "StreamRight")
	{
		WaterCourseRender->ChangeAnimation("D_StreamRight");
		PreAniName = "D_StreamRight";
	}
}

void AWaterCourse::DeleteTick(float _DeltaTime)
{
	// Animation Final Frame callback
	WaterCourseRender->SetLastFrameCallback(PreAniName, [=]()
		{
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
					if (type == EMapObjectType::Item)
					{
						NextMapObject->WaterInteract();
					}
				}
				
				if (NextMapObject == nullptr && UpEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, false, EEngineDir::Up);
				}
				else if (EMapObjectType::Item == NextMapObject->GetType() && false == UpEnd)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, false, EEngineDir::Up);
				}
			}

			if (12 >= GetCurPos().y + DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y + DefaultPowerValue, GetCurPos().x);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
					}
					DownEnd = true;
				}

				if (NextMapObject == nullptr && DownEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, false, EEngineDir::Down);
				}
			}

			if (0 <= GetCurPos().x - DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x - DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
					}
					LeftEnd = true;
				}

				if (NextMapObject == nullptr && LeftEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, false, EEngineDir::Left);
				}
			}

			if (14 >= GetCurPos().x + DefaultPowerValue)
			{
				POINT x = GetCurPos();
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x + DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
					}
					RightEnd = true;
				}

				if (NextMapObject == nullptr && RightEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, false, EEngineDir::Right);
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
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
					}
				}

				if (NextMapObject == nullptr && UpEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y - DefaultPowerValue, GetCurPos().x, true, EEngineDir::Up);
				}
			}

			if (12 >= GetCurPos().y + DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y + DefaultPowerValue, GetCurPos().x);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
					}
				}

				if (NextMapObject == nullptr && DownEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y + DefaultPowerValue, GetCurPos().x, true, EEngineDir::Down);
				}
			}

			if (0 <= GetCurPos().x - DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x - DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
					}
				}

				if (NextMapObject == nullptr && LeftEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x - DefaultPowerValue, true, EEngineDir::Left);
				}
			}

			if (14 >= GetCurPos().x + DefaultPowerValue)
			{
				std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(GetCurPos().y, GetCurPos().x + DefaultPowerValue);
				if (NextMapObject != nullptr)
				{
					EMapObjectType type = NextMapObject->GetType();
					if (type == EMapObjectType::Block)
					{
						NextMapObject->WaterInteract();
					}
				}

				if (NextMapObject == nullptr && RightEnd == false)
				{
					GetGameMode()->GetCurMap()->AddWaterCourse(GetCurPos().y, GetCurPos().x + DefaultPowerValue, true, EEngineDir::Right);
				}
			}
		}

		CreateStart = false; // Tick Control
	}

	

	//NextMapObject->WaterInteract();
}