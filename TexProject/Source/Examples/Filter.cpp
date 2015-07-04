#include <TexProject/TexProject.h>
using namespace TexProject;


Texture::D2* filter(Texture::D2* tex)
{
	auto res = new Texture::D2;

	res->Create(tex->GetSize());
	/*
	Створюємо вихідну текстуру того ж розміру
	*/

	for(uint32 x = 0; x < tex->GetSize().x; ++x)
	for(uint32 y = 0; y < tex->GetSize().y; ++y)
	{
		auto color = tex->GetPixel(uvec2(x,y));
		color = vec4(vec3(color.x + color.y + color.z)/3.0f,1.0f);
		res->SetPixel(uvec2(x,y),color);
		/*
		Заповнюємо пікселі вихідної текстури пікселями з вхідної, у чорно-білому форматі
		*/
	}

	return res;
}


void fInit(Window::Render* window)
{
	auto panel1 = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	auto panel2 = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	/*
	Створюємо панелі типу "зображення" і приводимо вказівник на неї до типу Interface::Panel::Image*
	*/
	panel1->SetPos(vec2(200.0f));
	panel1->SetSize(vec2(256.0f));
	panel2->SetSize(vec2(256.0f));
	/*
	Задаємо розмір панелей
	*/

	auto oldTex = new Texture::D2;
	oldTex->Load("Media/Images/Example.JPG");
	/*
	Завантажуємо зображення
	*/

	auto newTex = filter(oldTex);
	/*
	Викликаємо функцію фільтру
	*/

	panel1->SetImage(oldTex);
	panel2->SetImage(newTex);
	/*
	Задаємо зображення панелей
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












