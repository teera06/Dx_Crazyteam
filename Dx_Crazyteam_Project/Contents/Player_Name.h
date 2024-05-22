#pragma once
#include "CAObject.h"
#include <EngineCore/TextWidget.h>
#include <string>


class APlayer;
class APlayer_Name : public ACAObject
{
	GENERATED_BODY(ACAObject)


public:
	// constrcuter destructer
	APlayer_Name();
	~APlayer_Name();

	// delete Function
	APlayer_Name(const APlayer_Name& _Other) = delete;
	APlayer_Name(APlayer_Name&& _Other) noexcept = delete;
	APlayer_Name& operator=(const APlayer_Name& _Other) = delete;
	APlayer_Name& operator=(APlayer_Name&& _Other) noexcept = delete;

	UTextWidget* GetNameText()
	{
		return NameText;
	}




protected:

	void InsertName(std::string_view _Name);

	UTextWidget* NameText = nullptr;
	std::shared_ptr<APlayer> Player = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
};