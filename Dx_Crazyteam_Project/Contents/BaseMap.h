#pragma once

// Ό³Έν :
class BaseMap
{
public:
	// constructor destructor
	BaseMap();
	~BaseMap();

	// delete Function
	BaseMap(const BaseMap& _Other) = delete;
	BaseMap(BaseMap&& _Other) noexcept = delete;
	BaseMap& operator=(const BaseMap& _Other) = delete;
	BaseMap& operator=(BaseMap&& _Other) noexcept = delete;

protected:

private:

};

