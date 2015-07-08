#include <TexProject/TexProject.h>
using namespace TexProject;




void fInit(Window::Render* window)
{
	Tool::Init();

	auto panelTollbar = window->AddPanel(Interface::PanelTypes::Default);
	panelTollbar->SetSize(vec2(200.0f,32.0f));
	panelTollbar->SetPos(vec2(180.0f + panelTollbar->GetSize().x*0.5f,window->GetSize().y - panelTollbar->GetSize().y*0.5f));
	panelTollbar->LockMove();

	{
		auto b1 = (Interface::Button::Default*)panelTollbar->AddButton(Interface::ButtonTypes::Default);
		b1->SetPos(vec2(-panelTollbar->GetSize().x*0.5f + 16.0f + 32.0f*0,0.0f));
		b1->SetSize(vec2(24.0f));
		b1->SetAction
		(
			Interface::Item::ActionTypes::Click,
			[](Interface::Item* item)
			{
				Tool::Add<Tool::Generator::D2::Blank>(item->GetWindow());
			}
		);

		auto b2 = (Interface::Button::Default*)panelTollbar->AddButton(Interface::ButtonTypes::Default);
		b2->SetPos(vec2(-panelTollbar->GetSize().x*0.5f + 16.0f + 32.0f*1,0.0f));
		b2->SetSize(vec2(24.0f));
		b2->SetAction
		(
			Interface::Item::ActionTypes::Click,
			[](Interface::Item* item)
			{
				Tool::Add<Tool::Filter::D2::Correction::Color>(item->GetWindow());
			}
		);
	}

	auto panelConfig = window->AddPanel(Interface::PanelTypes::Default);
	panelConfig->SetSize(vec2(180.0f,float32(window->GetSize().y)));
	panelConfig->SetPos(panelConfig->GetSize()*0.5f);
	panelConfig->LockMove();
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












