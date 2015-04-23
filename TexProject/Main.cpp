/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;
using namespace TexProject::OpenGL;


Texture tTexture;

void TexInitFunc(Window::Render* window)
{
	/*
	Ця функція буде викликана одразу, як вікно буде створено.
	window - вказівник на вікно, яке викличе функцію.
	Тут ми виділяємо ресурси для подальшої роботи.
	*/

	Texture::InitDraw();	// Ініціалізуємо функції малювання для цього вікна

	tTexture.Resize(uvec3(256,256,1));	// Встановлюємо розмір текстури

	// Заповнюємо текстуру
	for(uint32 x = 0; x < tTexture.size.x; ++x)
	for(uint32 y = 0; y < tTexture.size.y; ++y)
	{
		vec4 color;

		{	// gradient
			color.x = float32(x)/float32(tTexture.size.x);
			color.y = float32(y)/float32(tTexture.size.y);
			color.z = 0.0f;
			color.w = 1.0f;
		}

		// position of pixel if 2xfloat32 format
		vec2 tPos;
		tPos.x = float32(x);
		tPos.y = float32(y);

		{	// outer shape
			vec2 pos;
			pos.x = tTexture.size.x*0.5f;
			pos.y = tTexture.size.y*0.5f;
			float32 innerRadius = tTexture.size.x*0.5f*0.9f;
			float32 outerRadius = tTexture.size.x*0.5f*1.0f;

			float32 d = dist(tPos,pos);
			if( d > innerRadius && d < outerRadius )
			{
				color.x = color.y = color.z = 1.0f;
			}
		}

		{	// left eye
			vec2 pos;
			pos.x = tTexture.size.x*(0.5f - 0.22f);
			pos.y = tTexture.size.y*0.68f;
			float32 outerRadius = tTexture.size.x*0.08f;

			float32 d = dist(tPos,pos);
			if(d < outerRadius)
			{
				color.x = color.y = color.z = 1.0f;
			}
		}

		{	// right eye
			vec2 pos;
			pos.x = tTexture.size.x*(0.5f + 0.22f);
			pos.y = tTexture.size.y*0.68f;
			float32 outerRadius = tTexture.size.x*0.08f;

			float32 d = dist(tPos,pos);
			if(d < outerRadius)
			{
				color.x = color.y = color.z = 1.0f;
			}
		}

		{	// smile
			vec2 pos;
			pos.x = tTexture.size.x*0.5f;
			pos.y = tTexture.size.y*(1.0f);
			float32 innerRadius = tTexture.size.x*0.75f;
			float32 outerRadius = tTexture.size.x*0.8f;
			float32 angularRange = 18.0f;

			float32 d = dist(tPos,pos);
			float32 a = getAng(vec2(0.0f,-1.0f),tPos-pos);
			if(d > innerRadius && d < outerRadius && a < angularRange)
			{
				color.x = color.y = color.z = 1.0f;
			}
		}

		tTexture.Get(x,y) = color;
	}

	// Будуємо текстуру
	tTexture.Build();
}
void TexRenderFunc(Window::Render* window)
{
	/*
	Ця функція буде викликатись для вікна 60 разів на секунду
	доти, доки вікно не закриють.
	*/

	tTexture.Draw();	// Виводимо текстуру
}
void TexFreeFunc(Window::Render* window)
{
	/*
	Ця функція викличеться перед видаленням вікна.
	В ній ми звільнюємо ресурси.
	*/

	tTexture.Delete();		// Очищаємо текстуру
	Texture::FreeDraw();	// Деініціалізуємо функції малювання
}


void TexProject::Main()
{
	Window::Render a;

	a.Create();
	a.SetFunc(Window::Render::FuncTypes::Init,TexInitFunc);		// Встановлюємо функції ініціалізації
	a.SetFunc(Window::Render::FuncTypes::Render,TexRenderFunc);	// Рендеру (обробки)
	a.SetFunc(Window::Render::FuncTypes::Free,TexFreeFunc);		// І звільнення ресурсів
	a.SetRenderContext(Window::RenderContext::Types::OpenGL);	// Встановлюємо контекст рендеру

	while(a.IsRunning())
	{
		Window::Process();

		if(KeyState(Keys::ESC)) break;
	}

	a.Delete();
}












