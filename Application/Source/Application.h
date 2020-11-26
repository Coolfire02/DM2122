
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"



class Application
{
public:
	Application();
	~Application();
	static bool IsKeyPressed(unsigned short key);
	void Init();
	void Run();
	void Exit();

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif