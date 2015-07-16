#include <TexProject/TexProject.h>
using namespace TexProject;




void fInit(Window::Render* window)
{
	Tool::Init(window);
}
void fFree(Window::Render* window)
{
	Tool::Free();
}
void fLoop(Window::Render* window)
{
	Tool::Loop();
}


void TexProject::Main()
{
	Window::Render wnd;
	Window::Render wnd1;

	wnd.SetFunc(Window::Render::FuncTypes::Init,fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free,fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop,fLoop);
	wnd.Create("window");
	wnd.SetSize(uvec2(800,600));
	wnd.SetRenderContext(Window::RenderContext::Type::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}












