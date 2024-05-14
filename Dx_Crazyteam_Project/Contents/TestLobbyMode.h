#pragma once

// Ό³Έν :
class TestLobbyMode
{
public:
	// constrcuter destructer
	TestLobbyMode();
	~TestLobbyMode();

	// delete Function
	TestLobbyMode(const TestLobbyMode& _Other) = delete;
	TestLobbyMode(TestLobbyMode&& _Other) noexcept = delete;
	TestLobbyMode& operator=(const TestLobbyMode& _Other) = delete;
	TestLobbyMode& operator=(TestLobbyMode&& _Other) noexcept = delete;

protected:

private:

};

