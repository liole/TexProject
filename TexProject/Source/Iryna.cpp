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
		vec4 color(0);
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
			
			res->SetPixel(uvec2(i, j), color / sum);
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
		vec3 a;
		if (i != 0)
		{
			if(i != tex->GetSize().x-1)
				a.x = tex->GetPixel(uvec2(i-1,j)).x - tex->GetPixel(uvec2(i+1,j)).x;
			else
				a.x = tex->GetPixel(uvec2(i-1,j)).x - tex->GetPixel(uvec2(i,j)).x;
		}
		else
			a.x = tex->GetPixel(uvec2(i,j)).x - tex->GetPixel(uvec2(i+1,j)).x;

		if(j != 0)
		{
			if(j != tex->GetSize().y-1)
				a.y = tex->GetPixel(uvec2(i,j-1)).x - tex->GetPixel(uvec2(i,j+1)).x;
			else
				a.y = tex->GetPixel(uvec2(i,j-1)).x - tex->GetPixel(uvec2(i,j)).x;
		}
		else
			a.y = tex->GetPixel(uvec2(i,j)).x - tex->GetPixel(uvec2(i,j+1)).x;
		a.z = 0.1f;
		a.normalize();
		a += vec3(1.0f);
		a *= vec3(0.5f);
		res->SetPixel(uvec2(i, j), vec4(a, 1.0f));
	}

	return res;
}


void fInit(Window::Render* window)
{
	auto panel1 = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);
	auto panel2 = (Interface::Panel::Image*)window->AddPanel(Interface::PanelTypes::Image);

	panel1->SetPos(vec2(200.0f));
	panel1->SetSize(vec2(512.0f));
	panel2->SetSize(vec2(512.0f));

	auto oldTex = new Texture::D2;
	oldTex->Load("Media/Images/Stone_HeightMap.png");

	auto newTex = HeightToNormal(oldTex);

	panel1->SetImage(oldTex);
	panel2->SetImage(newTex);
/*
	auto panel = window->AddPanel(Interface::PanelTypes::Default);
	auto im = panel -> AddPanel(Interface::PanelTypes::Image);
	panel ->SetSize(vec2(256.0f));
	im->SetSize(vec2(180.0f));
	panel->SetColor(vec4(0.32f));
	im->SetPos((panel->GetSize() - im->GetSize())/2.0f);
	auto but = panel ->AddButton(Interface::ButtonTypes::Default);
	but ->SetSize(vec2(80,20));
	but->SetPos(vec2((panel->GetSize().x-but->GetSize().x)/2.0f,4));
	auto butcl = panel ->AddButton(Interface::ButtonTypes::Close);
	butcl ->SetSize(vec2(20,20));
	butcl ->SetPos(panel->GetSize()-butcl->GetSize()-4.0f);
	but->SetUserData(im);
	but ->SetAction
	(
		Interface::Item::ActionTypes::Click,
		[](Interface::Item* item)
		{
			auto oldTex = new Texture::D2;
			oldTex->Load("Media/Images/Stone_HeightMap.png");
		
			auto newTex = HeightToNormal(oldTex);

			auto im = (Interface::Panel::Image*)item->GetUserData();
			im->SetImage(newTex);
		}
	);*/
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












