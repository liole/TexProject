#include <TexProject/TexProject.h>
using namespace TexProject;




void fInit(Window::Render* window)
{
	Tool::Init(window);


	/*auto a = new Texture::D2;
	a->Create(uvec2(16));

	for(uint32 x = 0; x < a->GetSize().x; ++x)
	for(uint32 y = 0; y < a->GetSize().y; ++y)
	{
		a->SetPixel(uvec2(x,y),vec4(float32(x)/a->GetSize().x,float32(y)/a->GetSize().y,0,1));
	}

	auto b = new Texture::D2;
	b->Create(uvec2(128));

	for(uint32 x = 0; x < b->GetSize().x; ++x)
	for(uint32 y = 0; y < b->GetSize().y; ++y)
	{
		vec2 d;
		d.x = float32(x) / (b->GetSize().x - 1) * 3.0f - 1.0f;
		d.y = float32(y) / (b->GetSize().y - 1) * 3.0f - 1.0f;
		b->SetPixel(uvec2(x,y),a->GetPixelLinearClamp(d));
	}

	auto t1 = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	t1->SetImage(a);
	auto t2 = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	t2->SetImage(b);
	t2->AddPos(vec2(100.0f));*/
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












