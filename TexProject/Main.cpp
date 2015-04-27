/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;
using namespace TexProject::OpenGL;


Texture* tTexture = nullptr;

/*Функція генерації текстури*/
Texture*	texGenFunc()
{
	auto tex = new Texture;

	tex->Resize(uvec3(512,512,1));

	for(uint32 x = 0; x < tex->GetSize().x; ++x)
	{
		for(uint32 y = 0; y < tex->GetSize().y; ++y)
		{
			vec4 color;

			{	// make a gradient
				color.x = float32(x)/float32(tex->GetSize().x);
				color.y = float32(y)/float32(tex->GetSize().y);
				color.z = 0.0f;
				color.w = 1.0f;
			}

			tex->Get(x,y) = color;
		}
	}

	tex->Build();

	return tex;
}


void TexInitFunc(Window::Render* window)
{
	/*
	Ця функція буде викликана одразу, як вікно буде створено.
	window - вказівник на вікно, яке викличе функцію.
	Тут ми виділяємо ресурси для подальшої роботи.
	*/

	Texture::InitDraw();	// Ініціалізуємо функції малювання для цього вікна

	if(tTexture)
	{
		delete tTexture;
		tTexture = nullptr;
	}
	tTexture = texGenFunc();

}
void TexRenderFunc(Window::Render* window)
{
	/*
	Ця функція буде викликатись для вікна 60 разів на секунду
	доти, доки вікно не закриють.
	*/

	if(tTexture)						// Виводимо текстуру
	{
		tTexture->Draw();
	}
}
void TexFreeFunc(Window::Render* window)
{
	/*
	Ця функція викличеться перед видаленням вікна.
	В ній ми звільнюємо ресурси.
	*/

	if(tTexture)						// Очищаємо текстуру
	{
		tTexture->Delete();
		tTexture = nullptr;
	}

	Texture::FreeDraw();				// Деініціалізуємо функції малювання
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.Create();
	tWindow.SetSize(uvec2(512,512));
	tWindow.SetFunc(Window::Render::FuncTypes::Init,TexInitFunc);		// Встановлюємо функції ініціалізації
	tWindow.SetFunc(Window::Render::FuncTypes::Render,TexRenderFunc);	// Рендеру (обробки)
	tWindow.SetFunc(Window::Render::FuncTypes::Free,TexFreeFunc);		// І звільнення ресурсів
	tWindow.SetRenderContext(Window::RenderContext::Types::OpenGL);		// Встановлюємо контекст рендеру

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}












