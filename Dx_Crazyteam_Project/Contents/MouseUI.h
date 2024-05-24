#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UImage;
class MouseUI : public AActor
{

	GENERATED_BODY(AActor)
public:

	// constrcuter destructer
	MouseUI();
	~MouseUI();

	// delete Function
	MouseUI(const MouseUI& _Other) = delete;
	MouseUI(MouseUI&& _Other) noexcept = delete;
	MouseUI& operator=(const MouseUI& _Other) = delete;
	MouseUI& operator=(MouseUI&& _Other) noexcept = delete;
	void SetMousePos();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTIme) override;

private:
	UImage* MouseRender = nullptr;
};

