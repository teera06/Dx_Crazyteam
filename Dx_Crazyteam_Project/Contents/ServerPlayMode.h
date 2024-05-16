#pragma once

// Ό³Έν :
class ServerPlayMode
{
public:
	// constrcuter destructer
	ServerPlayMode();
	~ServerPlayMode();

	// delete Function
	ServerPlayMode(const ServerPlayMode& _Other) = delete;
	ServerPlayMode(ServerPlayMode&& _Other) noexcept = delete;
	ServerPlayMode& operator=(const ServerPlayMode& _Other) = delete;
	ServerPlayMode& operator=(ServerPlayMode&& _Other) noexcept = delete;

protected:

private:

};

