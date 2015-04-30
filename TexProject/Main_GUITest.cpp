/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;


void windowInit(Window::Render* window)
{
	auto p1 = window->AddPanelDefault();
	p1->SetPos(vec2(400.0f,200.0f));
	auto p2 = window->AddPanelDefault();
	p2->SetSize(vec2(150.0f));
}
void windowLoop(Window::Render* window)
{
}
void windowFree(Window::Render* window)
{
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.SetFunc(Window::Render::FuncTypes::Init,windowInit);
	tWindow.SetFunc(Window::Render::FuncTypes::Free,windowFree);
	tWindow.SetFunc(Window::Render::FuncTypes::Loop,windowLoop);
	tWindow.Create();
	tWindow.SetSize(uvec2(512,512));
	tWindow.SetRenderContext(Window::RenderContext::Types::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}












