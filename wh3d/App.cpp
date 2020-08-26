#include "App.h"
#include<math.h>
#include <iomanip>
App::App() :wnd(800,600, "Z fuck Window")
{}
int App::Go() 
{
	while (true) 
	{
		if (const auto ecode = Window::ProcessMessages()) 
		{
			return *ecode;
		}
		DoFrame();
	}
}
void App::DoFrame()
{
	const float t = timer.Peek();
	const float c = std::sin(t) / 2.0f + 0.5f;

	//Çå³ýbuffer
	wnd.Gfx().ClearBuffer(0.0f, c, c);

	//Render a triangle
	wnd.Gfx().DrawTestTriangle(t,wnd.mouse.GetPosX(),wnd.mouse.GetPosY());

	//
	wnd.Gfx().EndFrame();
}