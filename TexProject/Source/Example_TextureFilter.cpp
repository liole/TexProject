#include <TexProject/TexProject.h>
using namespace TexProject;


Texture* tInputTexture = nullptr;		// Вхідна текстура фільтру
Texture* tOutputTexture = nullptr;		// Вихідна текстура фільтру


Texture* filterFunc(Texture* sourceTexture)
{
	auto tex = new Texture;
	tex->Resize(sourceTexture->GetSize());

	for(uint32 x = 0; x < tex->GetSize().x; ++x)
	{
		for(uint32 y = 0; y < tex->GetSize().y; ++y)
		{
			vec4 color;
			{	// turn into grayscale
				color = sourceTexture->Get(x,y);
				float t = sqrt((color.x*color.x + color.y*color.y + color.z*color.z)/3.0f);
				color = vec4(t,t,t,1.0f);
			}
			tex->Get(x,y) = color;
		}
	}

	return tex;
}


void TexInitFunc(Window::Render* window)
{
	Texture::InitDraw();	// Ініціалізуємо функції малювання для цього вікна

	if(!tInputTexture)
	{
		tInputTexture = new Texture;
		tInputTexture->Load("Media/Images/3.PNG");	// Завантажуємо вхідну текстуру
		tInputTexture->Build(window);
	}
	if(!tOutputTexture)
	{
		tOutputTexture = filterFunc(tInputTexture);
		tOutputTexture->Build(window);
	}
}
void TexRenderFunc(Window::Render* window)
{
	if(KeyState(Keys::SPACE))				// Якщо користувач натиснув пробіл
	{
		if(tOutputTexture)					// Виводимо вихідну текстуру
		{
			tOutputTexture->Draw();
		}
	}
	else
	{
		if(tInputTexture)					// Виводимо вхідну текстуру
		{
			tInputTexture->Draw();
		}
	}
}
void TexFreeFunc(Window::Render* window)
{
	if(tInputTexture)						// Очищаємо текстуру
	{
		delete tInputTexture;
		tInputTexture = nullptr;
	}
	if(tOutputTexture)						// Очищаємо текстуру
	{
		delete tOutputTexture;
		tOutputTexture = nullptr;
	}

	Texture::FreeDraw();				// Деініціалізуємо функції малювання
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.Create();
	tWindow.SetSize(uvec2(256,256));
	tWindow.SetFunc(Window::Render::FuncTypes::Init,TexInitFunc);		// Встановлюємо функції ініціалізації
	tWindow.SetFunc(Window::Render::FuncTypes::Loop,TexRenderFunc);		// Рендеру (обробки)
	tWindow.SetFunc(Window::Render::FuncTypes::Free,TexFreeFunc);		// І звільнення ресурсів
	tWindow.SetRenderContext(Window::RenderContext::Types::OpenGL);		// Встановлюємо контекст рендеру

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}












