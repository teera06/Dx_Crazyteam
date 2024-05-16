#pragma once
#include "CAObject.h"

// Ό³Έν :
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
	
	void DepthUpdate();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	EMapObjectType Type = EMapObjectType::None;
	POINT CurPos = { 0,0 };

};

