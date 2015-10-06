#include <TexProject/TexProject.h>
using namespace TexProject;

ToolSet*				toolSet = nullptr;

void funcInit(Window* window)
{
	toolSet = new ToolSet(window);
}
void funcFree(Window* window)
{
	if(toolSet) { delete toolSet; toolSet = nullptr; }
}
void funcLoop(Window* window)
{
	toolSet->Loop();
}

void TexProject::Main()
{
	Window wnd;

	wnd.EnableVSync();
	wnd.SetFunc(Window::FuncType::Init,funcInit);
	wnd.SetFunc(Window::FuncType::Free,funcFree);
	wnd.SetFunc(Window::FuncType::Loop,funcLoop);
	wnd.Create();
	wnd.SetRenderContext(RenderContext::Type::Default);

	while(Window::Process())
	{
		if(KeyState(Key::ESC)) break;
	}

	wnd.Delete();
}