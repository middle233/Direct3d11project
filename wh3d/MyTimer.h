#pragma once
#include<chrono>
class MyTimer
{
public:
	MyTimer();
	float Mark();
	float Peek() const;
private:
	std::chrono::steady_clock::time_point last;
};

