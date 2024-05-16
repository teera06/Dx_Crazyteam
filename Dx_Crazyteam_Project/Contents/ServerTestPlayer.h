#pragma once

// Ό³Έν :
class ServerTestPlayer
{
public:
	// constrcuter destructer
	ServerTestPlayer();
	~ServerTestPlayer();

	// delete Function
	ServerTestPlayer(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer(ServerTestPlayer&& _Other) noexcept = delete;
	ServerTestPlayer& operator=(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer& operator=(ServerTestPlayer&& _Other) noexcept = delete;

protected:

private:

};

