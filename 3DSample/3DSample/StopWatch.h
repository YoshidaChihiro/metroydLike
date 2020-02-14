#pragma once
#include<time.h>
#include<ctime>
#include <chrono>
namespace Framework {
	class StopWatch
	{
	public:
		StopWatch();
		void Start();


		std::chrono::milliseconds GetTime();
	private:

		timespec startTime;
		timespec nowTime;
		timespec deltaTime;
	};

}