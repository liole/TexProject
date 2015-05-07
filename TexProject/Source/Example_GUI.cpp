/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
*/
#include <TexProject/TexProject.h>
using namespace TexProject;


Texture* tex;


void windowInit(Window::Render* window)
{
	auto p1 = window->AddPanel(Interface::PanelTypes::Default);
	p1->SetPos(vec2(400.0f,200.0f));
	p1->SetSize(vec2(200.0f,100.0f));

	auto b1 = p1->AddButton(Interface::ButtonTypes::Close);	// Add Button to panel p1
	b1->SetPos(vec2(100.0f-15.0f,-50.0f+15.0f));
	b1->SetSize(vec2(24.0f));

	auto p2 = window->AddPanel(Interface::PanelTypes::Default);
	p2->SetPos(vec2(200.0f,50.0f));
	p2->SetSize(vec2(150.0f));

	auto b2 = p2->AddButton(Interface::ButtonTypes::Close);	// Add Button to panel p2
	b2->SetPos(vec2(75.0f-15.0f,-75.0f+15.0f));
	b2->SetSize(vec2(24.0f));

	auto b3 = p2->AddButton(Interface::ButtonTypes::Default);
	b3->SetSize(vec2(80.0f,24.0f));
	b3->SetAction(Interface::Item::ActionTypes::Click,[](Interface::Item*){Message("Action occured.");});
	

	auto basicPropertyPanel = window->AddPanel(Interface::PanelTypes::Default);
	basicPropertyPanel->SetSize(vec2(200.0f,window->GetSize().y));
	basicPropertyPanel->SetPos(vec2(100.0f,window->GetSize().y*0.5f));
	basicPropertyPanel->LockMove();


	//tex = new Texture;
	//tex->Load("Media/Images/3.png");
	tex = Generator::Noise::Perlin(uvec3(uvec2(256),1));
	tex->Build(window);

	auto panelImage = (Interface::GUIPanelImage*)window->AddPanel(Interface::PanelTypes::Image);
	panelImage->SetSize(vec2(tex->GetSize().xy()));
	panelImage->SetImage(tex);
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.SetFunc(Window::Render::FuncTypes::Init,windowInit);
	tWindow.Create();
	tWindow.SetSize(uvec2(800,600));
	tWindow.SetRenderContext(Window::RenderContext::Types::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}












