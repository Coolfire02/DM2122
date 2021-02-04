
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

	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double* xpos, double* ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();
	static unsigned m_width;
	static unsigned m_height;

private:
	int mainScene;
	//Declare a window object
	StopWatch m_timer;
};

#endif