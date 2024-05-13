#pragma once

class Intro
{
public:
	// constrcuter destructer
	Intro();
	~Intro();

	// delete Function
	Intro(const Intro& _Other) = delete;
	Intro(Intro&& _Other) noexcept = delete;
	Intro& operator=(const Intro& _Other) = delete;
	Intro& operator=(Intro&& _Other) noexcept = delete;

protected:

private:

};

