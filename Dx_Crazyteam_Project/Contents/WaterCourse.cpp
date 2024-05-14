#include "PreCompile.h"
#include "WaterCourse.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "BaseMap.h"
#include "CAGameMode.h"

AWaterCourse::AWaterCourse()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

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

	WaterCourseRender->SetAutoSize(20.0f, true);
	WaterCourseRender->SetActive(false);
}

void AWaterCourse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);
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
	WaterCourseRender->CreateAnimation("Water_Center", "Center11.png", 0.125f, true);

	{
		// 물줄기 뻗어 나갈 때 사용할 애니메이션
		WaterCourseRender->CreateAnimation("CreateUp", "up12.png", 0.125f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateDown", "down12.png", 0.125f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateLeft", "left12.png", 0.125f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateRight", "right12.png", 0.125f, true, 0, 0);
	}

	{
		// 물 끝. -> Tick에서 사용할 애니메이션.
		WaterCourseRender->CreateAnimation("EndStemUp", "up12.png", 0.125f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemDown", "down12.png", 0.125f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemLeft", "left12.png", 0.125f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemRight", "right12.png", 0.125f, true, 0, 1);

		// 물 줄기 중간 -> Tick에서 사용할 애니메이션.
		WaterCourseRender->CreateAnimation("StreamUp", "up22.png", 0.125f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamDown", "down22.png", 0.125f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamLeft", "left22.png", 0.125f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamRight", "right22.png", 0.125f, true, 0, 2);
	}

	{
		// 물 끝 사라짐.
		WaterCourseRender->CreateAnimation("EndStemUp_D", "up12.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("EndStemDown_D", "down12.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("EndStemLeft_D", "left12.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("EndStemRight_D", "right12.png", 0.125f, true, 1, 10);

		// 물 줄기 사라짐.
		WaterCourseRender->CreateAnimation("StreamUp_D", "up22.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("StreamDown_D", "down22.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("StreamLeft_D", "left22.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("StreamRight_D", "right22.png", 0.125f, true, 1, 10);
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
	LifeTime = 0.0f;
	CreateTime = 0.0f;
}
void AWaterCourse::CreateCenterTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;
	CreateTime += _DeltaTime;
	if (2.0f <= LifeTime)
	{
		State.ChangeState("Delete");
		return;
	}

	for (size_t i = 0; i < PowerValue; i++)
	{
		if (0.5f <= CreateTime)
		{
			// 만들어 질 곳에 뭐가 있음?


			std::shared_ptr<AWaterCourse> Stem = GetWorld()->SpawnActor<AWaterCourse>("Stream");
			//Stem->GetGameMode()->GetCurMap()->GetMapObject

			//std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject()
			//Stem->CreateWaterStream();

			//CreateTime = 0.0f;
		}
	}
}
void AWaterCourse::CreateCenterExit()
{
	LifeTime = 0.0f;
}
#pragma endregion

#pragma region CreateStream
void AWaterCourse::CreateStreamBegin()
{
	WaterCourseRender->SetActive(true);
}
void AWaterCourse::CreateStreamTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;

	if (1.0f <= LifeTime)
	{
		State.ChangeState("Delete");
		return;
	}
}
void AWaterCourse::CreateStreamExit()
{
	LifeTime = 0.0f;
	WaterCourseRender->SetActive(false);
}
#pragma endregion

#pragma region CreateEndStem  TODO
void AWaterCourse::CreateEndStemBegin()
{
}
void AWaterCourse::CreateEndStemTick(float _DeltaTime)
{
}
void AWaterCourse::CreateEndStemExit()
{
}
#pragma endregion



#pragma region Delete
void AWaterCourse::DeleteBegin()
{
}

void AWaterCourse::DeleteTick(float _DeltaTime)
{
	// Animation Final Frame callback
	
}

void AWaterCourse::DeleteExit()
{
}
#pragma endregion