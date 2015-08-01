#include <TexProject/TexProject.h>
using namespace TexProject;


#include <iostream>
#include <fstream>


void fInit(Window::Render* window)
{
	Lexer lexer("Media/Scripts/Lexer.lxr");

	string source;
	std::getline(std::ifstream("Media/Scripts/Script1.txt"),source,'\0');

	auto t = lexer.tokenize(source);
}
void fFree(Window::Render* window)
{
}
void fLoop(Window::Render* window)
{
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












