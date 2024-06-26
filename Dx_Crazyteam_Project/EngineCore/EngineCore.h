#pragma once

#include <map>
#include <string>
#include <string_view>

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineTime.h>
#include <EngineBase/ThreadPool.h>

#include "EngineGraphicDevice.h"
#include "EngineOption.h"
#include "EngineEnums.h"

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

class UserCore
{
public:
	virtual void End() = 0;
	virtual void Initialize() = 0;
	virtual void WindowOpen(std::string& _OutWindowTitle, std::string& _SmallIconPath) {}
};

// 설명 :
class AActor;
class ULevel;
class UEngineCore
{
public:
	friend ULevel;

	bool IsDebug;

	// constrcuter destructer
	UEngineCore();
	~UEngineCore();

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	template<typename UserCoreType>
	static void Start(HINSTANCE _Inst)
	{
		UEngineCore Core;
		UserCoreType UserCore;
		Core.UserCorePtr = &UserCore;
		Core.EngineStart(_Inst);
	}

	void SetWindowScale(FVector _Scale)
	{
		EngineWindow.SetWindowScale(_Scale);
	}

	UEngineGraphicDevice& GetEngineDevice()
	{
		return EngineDevice;
	}

	struct ID3D11Device* GetDirectXDevice()
	{
		return EngineDevice.GetDevice();
	}

	struct ID3D11DeviceContext* GetDirectXContext()
	{
		return EngineDevice.GetContext();
	}
	
	void ChangeLevel(std::string_view _Name, EMapType _MapType=EMapType::None);
	

	template<typename GameModeType>
	void CreateLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (true == Levels.contains(UpperName))
		{
			MsgBoxAssert("이미 존재하는 레벨을 또 만들려고 했습니다.");
			return;
		}



		std::shared_ptr<GameModeType> NewGameMode = std::make_shared<GameModeType>();
		std::shared_ptr<ULevel> Level = NewLevelCreate(_Name, NewGameMode);

		NewGameMode->SetOrder(INT_MIN);

	}

	template<typename GameModeType>
	std::shared_ptr<GameModeType> CreateLevel(std::string_view _Name , int Set)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (true == Levels.contains(UpperName))
		{
			MsgBoxAssert("이미 존재하는 레벨을 또 만들려고 했습니다.");
			return nullptr;
		}



		std::shared_ptr<GameModeType> NewGameMode = std::make_shared<GameModeType>();
		std::shared_ptr<ULevel> Level = NewLevelCreate(_Name, NewGameMode);

		NewGameMode->SetOrder(INT_MIN);

		return NewGameMode;
	}


	void DestroyLevel(std::string_view _Name)
	{
		std::string UpperName = UEngineString::ToUpper(_Name);

		if (false == Levels.contains(UpperName))
		{
			MsgBoxAssert(std::string(_Name) + "존재하지 않는 레벨을 파괴할수는 없습니다");
		}

		DestroyLevelName.push_back(UpperName);
	}

	FEngineOption GetEngineOption()
	{
		return EngineOption;
	}

	UEngineWindow EngineWindow;

	void SetGlobalTimeScale(float _Value)
	{
		GlobalTimeScale = _Value;
	}

	template<typename EnumType>
	void SetOrderTimeScale(EnumType _Order, float _Value)
	{
		SetOrderTimeScale(static_cast<int>(_Order), _Value);
	}

	void SetOrderTimeScale(int _Order, float _Value = 1.0f)
	{
		TimeScales[_Order] = _Value;
	}

	UThreadPool JobWorker;

	static ULevel* GetCurCreateLevel()
	{
		return CurCreateLevel;
	}

	void SetFrame(int _Frame)
	{
		Frame = _Frame;
		FrameTime = 1 / static_cast<float>(Frame);
	}


protected:

private:
	static ULevel* CurCreateLevel;

	FEngineOption EngineOption;

	UEngineTime MainTimer;

	std::string WindowIconPath;

	UEngineGraphicDevice EngineDevice;

	UserCore* UserCorePtr = nullptr;

	std::map <std::string, std::shared_ptr<ULevel>> Levels;
	std::shared_ptr<ULevel> NextLevel = nullptr;
	std::shared_ptr<ULevel> CurLevel = nullptr;

	std::vector<std::string> DestroyLevelName;

	int Frame = -1;
	float FrameTime = 0.0f;
	float CurFrameTime = 0.0f;

	void EngineOptionInit();

	void EngineStart(HINSTANCE _Inst);

	void EngineFrameUpdate();
	void EngineEnd();

	std::shared_ptr<ULevel> NewLevelCreate(std::string_view _Name, std::shared_ptr<AActor> _GameMode);

	float GlobalTimeScale = 1.0f;
	std::map<int, float> TimeScales;
};

extern UEngineCore* GEngine;