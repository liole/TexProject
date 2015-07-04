#include <TexProject/TexProject.h>
using namespace TexProject;


Texture::D2* generator()
{
	auto tex = new Texture::D2;
	/*
	Створюємо об"єкт "2D текстура"
	*/
	//tex->Create(uvec2(128));	// Замість створювати текстуру з нуля - краще завантажимо!
	tex->Load("Media/Images/Brick1_D.png");
	/*
	Завантажуємо зображення
	*/
	for(uint32 x = tex->GetSize().x/2; x < tex->GetSize().x; ++x)
	for(uint32 y = 0; y < tex->GetSize().y; ++y)
	{
		auto color = tex->GetPixel(uvec2(x,y));
		/*
		Отримуємо значення пікселя
		*/
		tex->SetPixel(uvec2(x,y),color*0.5f);
		/*
		Задаємо значення пікселя
		*/
	}
	/*
	Колір правої частини зображення множимо на 0.5
	*/
	return tex;
}


void fInit(Window::Render* window)
{
	auto panel = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	/*
	Створюємо панель типу "зображення" і приводимо вказівник на неї до типу Interface::Panel::Image*
	*/
	panel->SetSize(vec2(256.0f));
	/*
	Задаємо розмір панелі
	*/
	panel->SetImage(generator());
	/*
	Задаємо зображення панелі, отримане з генератора
	*/
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

	wnd.SetFunc(Window::Render::FuncTypes::Init,fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free,fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop,fLoop);
	wnd.Create("Generator Example");
	wnd.SetSize(uvec2(800,600));
	wnd.SetRenderContext(Window::RenderContext::Type::Default);

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}












