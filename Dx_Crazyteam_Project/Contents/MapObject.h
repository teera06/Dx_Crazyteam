#pragma once
#include "CAObject.h"

// 설명 :
class UDefaultSceneComponent;
class AMapObject : public ACAObject, public std::enable_shared_from_this<AMapObject>
{
	GENERATED_BODY(ACAObject)
public:
	// constructor destructor
	AMapObject();
	~AMapObject();

	// delete Function
	AMapObject(const AMapObject& _Other) = delete;
	AMapObject(AMapObject&& _Other) noexcept = delete;
	AMapObject& operator=(const AMapObject& _Other) = delete;
	AMapObject& operator=(AMapObject&& _Other) noexcept = delete;

	EMapObjectType GetType()
	{
		return Type;
	}

	void SetType(EMapObjectType _Type)
	{
		Type = _Type;
	}

	void SetCurPos(POINT _Pos)
	{
		CurPos = _Pos;
	}

	POINT GetCurPos()
	{
		return CurPos;
	}

	std::function<void()> PlayerInteract;
	std::function<void()> WaterInteract;

	void RendererOn()
	{
		Renderer->SetActive(true);

	}
	void RendererOff()
	{
		Renderer->SetActive(false);
	}

	void SetIsPossessed(bool _IsPossess)
	{
		IsPossessed = _IsPossess;
	}


	bool GetIsPossessed() const
	{
		return IsPossessed;
	}
	
	void DepthUpdate();

	void SetPossessItem(EItemType _Item)
	{
		PossessItem = _Item;
	}

	EItemType GetPossessItem()
	{
		return PossessItem;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	EMapObjectType Type = EMapObjectType::None;
	POINT CurPos = { 0,0 };

	//bush 관련 변수
	bool IsPossessed = false;

	EItemType PossessItem = EItemType::None;

};

