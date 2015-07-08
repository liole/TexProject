#include <TexProject/TexProject.h>
using namespace TexProject;

enum class DotsAllocation{Default, Circle, Square};
enum class PixelDef{Default, Double};
enum class ColorSettings{Default, Light, Dark, Custom};

void DefaultPixelDef(vec2* dotArr, uint32 dotNumber, uvec2 size, Texture::D2* tex, ColorSettings cs)
{
	vec4 color;
	for (uint32 x = 0; x < size.x; ++x)
	{
		for (uint32 y = 0; y < size.y; ++y)
		{
			float32 mindist = size.x*size.y;


			for (int i = 0; i < dotNumber; ++i)
			{
				float32 absx = fabs(float32(x) - dotArr[i].x);
				float32 absy = fabs(float32(y) - dotArr[i].y);
				if (absx > size.x / 2) absx = float32(size.x) - absx;
				if (absy > size.y / 2) absy = float32(size.y) - absy;
				float32 dist = sqrtf(absx*absx + absy*absy);
				if (dist < mindist) mindist = dist;
			}

			//розширити
			color.x = (1.0f - mindist / 100.0f)*0.45f;
			color.y = (1.0f - mindist / 100.0f)*0.88f;
			color.z = (1.0f - mindist / 100.0f)*0.50;
			color.w = (1.0f - mindist / 100.0f)*1.0f;

			tex->SetPixel(uvec2(x, y), color);
		}
	}
}

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
	for (uint32 x = tex->GetSize().x / 2; x < tex->GetSize().x; ++x)
		for (uint32 y = 0; y < tex->GetSize().y; ++y)
		{
		auto color = tex->GetPixel(uvec2(x, y));
		/*
		Отримуємо значення пікселя
		*/
		tex->SetPixel(uvec2(x, y), color*0.5f);
		/*
		Задаємо значення пікселя
		*/
		}
	/*
	Колір правої частини зображення множимо на 0.5
	*/
	return tex;
}

Texture::D2* WorleyGen(
	uvec2 size, uint32 dotNumber, 
	DotsAllocation da = DotsAllocation::Default, 
	PixelDef pdf = PixelDef::Default, 
	ColorSettings cs = ColorSettings::Default
	)
{
	auto tex = new Texture::D2;
	tex->Create(size);
	vec2* dotArr = new vec2[dotNumber];
	switch (da)
	{
		//розширити
		case DotsAllocation::Default :
			for (uint32 i = 0; i < dotNumber; ++i)
			{
				dotArr[i].x = rand() % size.x;
				dotArr[i].y = rand() % size.y;
			}
			break;
			
		default: 
			throw new Exception("wrong DotsAllocation argument");
			break;
	}

	//розширити
	switch (pdf)
	{
	case PixelDef::Default: 
		DefaultPixelDef(dotArr, dotNumber, size, tex, cs);
		break;
	default:
		throw new Exception("wrong PixelDef argument");
		break;
	}

	return tex;
}

void fInit(Window::Render* window)
{
	auto panel = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	/*
	Створюємо панель типу "зображення" і приводимо вказівник на неї до типу Interface::Panel::Image*
	*/
	panel->SetSize(vec2(512.0f));
	/*
	Задаємо розмір панелі
	*/
	panel->SetImage(WorleyGen(uvec2(512.0f), 100));
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

	wnd.SetFunc(Window::Render::FuncTypes::Init, fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free, fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop, fLoop);
	wnd.Create("Worley noise, alfa");
	wnd.SetSize(uvec2(800, 600));
	wnd.SetRenderContext(Window::RenderContext::Type::Default);

	while (Window::Process())
	{
		if (KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}












