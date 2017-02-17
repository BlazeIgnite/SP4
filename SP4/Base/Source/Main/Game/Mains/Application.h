
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Update();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();

	static void SetWindowWidth(const int&);
	static void SetWindowHeight(const int&);

private:
	Application();
	~Application();

	static int ScreenHeight;
	static int ScreenWidth;

	//Declare a window object
	StopWatch m_timer;
	double m_dElaspedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;
};

#endif