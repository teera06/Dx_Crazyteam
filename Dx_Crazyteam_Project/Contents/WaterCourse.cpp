#include "PreCompile.h"
#include "WaterCourse.h"
#include <EngineCore/DefaultSceneComponent.h>

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

	WaterCourseRender->SetAutoSize(5.0f, true);
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
	State.CreateState("Create");
	State.CreateState("Delete");

	State.SetStartFunction("None", std::bind(&AWaterCourse::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&AWaterCourse::NoneTick, this, std::placeholders::_1));

	State.SetFunction("Create",
		std::bind(&AWaterCourse::CreateBegin, this),
		std::bind(&AWaterCourse::CreateTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::CreateExit, this));
	State.SetFunction("Delete",
		std::bind(&AWaterCourse::DeleteBegin, this),
		std::bind(&AWaterCourse::DeleteTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::DeleteExit, this));

	State.ChangeState("None");
}


void AWaterCourse::CreateAnimation()
{
	WaterCourseRender->CreateAnimation("Water_Center", "Center11.png", 0.125f, true); // 중
	WaterCourseRender->CreateAnimation("Water_Up_Tick", "up12.png", 0.125f, true); // 상중
	WaterCourseRender->CreateAnimation("Water_Up_Exit", "up22.png", 0.125f, true); // 상끝
	WaterCourseRender->CreateAnimation("Water_Down_Tick", "down12.png", 0.125f, true); // 하중
	WaterCourseRender->CreateAnimation("Water_Down_Exit", "down22.png", 0.125f, true); // 하끝
	WaterCourseRender->CreateAnimation("Water_Left_Tick", "left12.png", 0.125f, true); // 좌중
	WaterCourseRender->CreateAnimation("Water_Left_Exit", "left22.png", 0.125f, true); // 좌끝
	WaterCourseRender->CreateAnimation("Water_Right_Tick", "right12.png", 0.125f, true); // 우중
	WaterCourseRender->CreateAnimation("Water_Right_Exit", "right12.png", 0.125f, true); // 우끝

	WaterCourseRender->ChangeAnimation("Water_Center");
}

#pragma region WallCling
void AWaterCourse::NoneBegin()
{
}

void AWaterCourse::NoneTick(float _DeltaTime)
{
}
#pragma endregion

#pragma region Create
void AWaterCourse::CreateBegin()
{
	// change Animation
	switch (Dir)
	{
	case EEngineDir::Right :
	{
		ChangeAnimation("Right", b_TheEnd);
		break;
	}
	case EEngineDir::Left :
	{
		ChangeAnimation("Left", b_TheEnd);
		break;
	}
	case EEngineDir::Up :
	{
		ChangeAnimation("Up", b_TheEnd);
		break;
	}
	case EEngineDir::Down :
	{
		ChangeAnimation("Down", b_TheEnd);
		break;
	}
	default :
		break;
	}

	WaterCourseRender->SetActive(true);
	WaterCourseRender->ChangeAnimation("Water_Center");
	LifeTime = 0.0f;
}

void AWaterCourse::ChangeAnimation(std::string_view _AniName, bool _Val)
{
	std::string AniName = "";
	AniName += _AniName;

	if (true == _Val)
	{
		WaterCourseRender->ChangeAnimation(AniName);
	}
	else
	{
		WaterCourseRender->ChangeAnimation(AniName);
	}
}

void AWaterCourse::CreateTick(float _DeltaTime)
{
	LifeTime += _DeltaTime;

	//if (1.0f <= LifeTime)
	//{
	//	State.ChangeState("Delete");
	//	return;
	//}
}

void AWaterCourse::CreateExit()
{
	LifeTime = 0.0f;
	WaterCourseRender->SetActive(false);
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