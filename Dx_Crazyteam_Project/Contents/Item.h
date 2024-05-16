#pragma once
#include "MapObject.h"
#include "ContentsEnum.h"

class AItem : public AMapObject
{
	GENERATED_BODY(AMapObject)
public:
	AItem();
	~AItem();

	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void Action() = 0;

	
private:

};

