#include <TexProject/TexProject.h>
using namespace TexProject;


Texture::D2* filter(Texture::D2* tex)
{
	auto res = new Texture::D2;

	res->Create(tex->GetSize());
	/*
	Створюємо вихідну текстуру того ж розміру
	*/

	for (uint32 x = 0; x < tex->GetSize().x; ++x)
	for (uint32 y = 0; y < tex->GetSize().y; ++y)
	{

		auto color = tex->GetPixel(uvec2(x, y));

		color = vec4(vec3(color.x + color.y + color.z) / 3.0f, 1.0f);

		res->SetPixel(uvec2(x, y), color);
		/*
		Заповнюємо пікселі вихідної текстури пікселями з вхідної, у чорно-білому форматі
		*/
	}

	return res;
}

Texture::D2* Blur(Texture::D2* tex)
{

	auto res = new Texture::D2;
	res->Create(tex->GetSize());


	for (uint32 i = 0; i < tex->GetSize().x; ++i)
	for (uint32 j = 0; j < tex->GetSize().y; ++j)
	{
		/*auto color = tex->GetPixel(uvec2(i, j));
		color = vec4(vec3(color.x + color.y + color.z) / 3.0f, 1.0f);
		res->SetPixel(uvec2(i, j), color);*/
		float32 sum = 0;
		vec4 color(tex->GetPixel(uvec2(i, j)));
		for (uint32 k = i - 3; k <= i + 3; ++k)
		for (uint32 l = j - 3; l <= j + 3; ++l)
		{

			if (k >= 0 && l >= 0 && k  < tex->GetSize().x && l  < tex->GetSize().y)
			{
				if (k == i - 3 || l == j - 3 || k == i + 3 || l == j + 3)
				{
					sum += (1.0f / 4);
					color += tex->GetPixel(uvec2(k, l))*(1.0f / 4);
				}
				else
				{
					if (k == i - 2 || l == j - 2 || k == i + 2 || l == j + 2)
					{
						sum += (1.0f / 3);
						color += tex->GetPixel(uvec2(k, l))*(1.0f / 3);
					}
					else
					{
						if (k == i - 1 || l == j - 1 || k == i + 1 || l == j + 1)
						{
							sum += (1.0f / 2);
							color += tex->GetPixel(uvec2(k, l))*(1.0f / 2);
						}
						else
						{
							sum += 1.0f;
							color += tex->GetPixel(uvec2(k, l));
						}
					}
				}
			}
			float32 w = 1.0f + 24 * (1.0f / 4) + 16 * (1.0f / 3) + 8 * (1.0f / 2);
			if (sum == w)
			{
				res->SetPixel(uvec2(i, j), color / sum);
			}
			//res->SetPixel(uvec2(i, j), color / sum);
		}

	}

	return res;
}


Texture::D2* HeightToNormal(Texture::D2* tex)
{
	auto res = new Texture::D2;
	res->Create(tex->GetSize());

	for (uint32 i = 0; i < tex->GetSize().x; ++i)
	for (uint32 j = 0; j < tex->GetSize().y; ++j)
	{
		vec3 a(0);
		if (i != 0)
		{
			a += vec3(0.0f, 1.0f, tex->GetPixel(uvec2(i - 1, j)).x - tex->GetPixel(uvec2(i, j)).x);
		}
		if (i != tex->GetSize().x - 1)
		{
			a += vec3(0.0f, 1.0f, tex->GetPixel(uvec2(i, j)).x - tex->GetPixel(uvec2(i + 1, j)).x);
		}

		if (j != 0)
		{
			a += vec3(tex->GetPixel(uvec2(i, j - 1)).x - tex->GetPixel(uvec2(i, j)).x, 1.0f, 0.0f);
		}
		if (j != tex->GetSize().y - 1)
		{
			a += vec3(tex->GetPixel(uvec2(i, j)).x - tex->GetPixel(uvec2(i, j + 1)).x, 1.0f, 0.0f);
		}
		a.y = 0.2f;
		a.normalize();
		a += vec3(1.0f, 1.0f, 1.0f);
		a /= vec3(2.0f, 2.0f, 2.0f);
		auto g = a.y;
		a.y = a.z;
		a.z = g;
		res->SetPixel(uvec2(i, j), vec4(a, 1.0f));
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
	oldTex->Load("Media/Images/Stone_HeightMap.png");
	/*
	Завантажуємо зображення
	*/

	auto newTex = HeightToNormal(oldTex);
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

	wnd.SetFunc(Window::Render::FuncTypes::Init, fInit);
	wnd.SetFunc(Window::Render::FuncTypes::Free, fFree);
	wnd.SetFunc(Window::Render::FuncTypes::Loop, fLoop);
	wnd.Create("Generator Example");
	wnd.SetSize(uvec2(800, 600));
	wnd.SetRenderContext(Window::RenderContext::Type::Default);

	while (Window::Process())
	{
		if (KeyState(Keys::ESC)) break;
	}

	wnd.Delete();
}












