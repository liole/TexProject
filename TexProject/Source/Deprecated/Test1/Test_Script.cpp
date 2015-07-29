#include <TexProject/TexProject.h>
using namespace TexProject;




void fInit(Window::Render* window)
{
	Texture::D2 in0;
	Texture::D2 in1;

	Script s;

	//s.AddInput(in0);
	//s.AddInput(in1);
	s.SetOutput(Texture::Type::D2,uvec3(128),1);

	s.Compile();
	auto t = s.Run();

	auto p = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	p->SetImage( (Texture::D2*)t[0] );
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












