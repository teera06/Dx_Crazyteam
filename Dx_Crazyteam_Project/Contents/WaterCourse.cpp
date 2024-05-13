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

	WaterCourseRender->SetAutoSize(1.0f, true);
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
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 醞
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 鼻
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // ж
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 謝
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 辦
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 部 鼻
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 部 ж
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 部 謝
	WaterCourseRender->CreateAnimation("", "", 0.125f, true); // 部 辦


	WaterCourseRender->ChangeAnimation("");
}


void AWaterCourse::NoneBegin()
{
}

void AWaterCourse::NoneTick(float _DeltaTime)
{
}

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

	if (1.0f <= LifeTime)
	{
		State.ChangeState("Delete");
		return;
	}
}

void AWaterCourse::CreateExit()
{
	LifeTime = 0.0f;
	WaterCourseRender->SetActive(false);
}



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
