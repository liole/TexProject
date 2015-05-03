/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
*/
#include <TexProject/TexProject.h>
using namespace TexProject;
using namespace TexProject::OpenGL;

const uint32 texSize = 512;
const uint32 octaves = 10;
const float32 frequencyStart = 5;

Texture* tTexture = nullptr;

float32 Noise2D(uint32 x, uint32 y)
{
	uint32 n = x + y * 57;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}
float32 SmoothedNoise2D(float32 x, float32 y)
{
	float32 corners = (Noise2D(x - 1, y - 1) + Noise2D(x + 1, y - 1) + Noise2D(x - 1, y + 1) + Noise2D(x + 1, y + 1)) / 16;
	float32 sides = (Noise2D(x - 1, y) + Noise2D(x + 1, y) + Noise2D(x, y - 1) + Noise2D(x, y + 1)) / 8;
	float32 center = Noise2D(x, y) / 4;
	return corners + sides + center;
}
float32 Cosine_Interpolate(float32 a, float32 b, float32 x)
{
	float32 ft = x * _PIf;
	float32 f = (1 - cos(ft)) * 0.5f;
	return  a*(1 - f) + b*f;
}
float32 Linear_Interpolate(float32 a, float32 b, float32 x)
{
	return a*(1 - x) + b*x;
}
float32 CompileNoise(float32 x, float32 y)
{
	float32 int_X = int(x);
	float32 fractional_X = x - int_X;
	float32 int_Y = int(y);
	float32 fractional_Y = y - int_Y;
	float32 v1 = SmoothedNoise2D(int_X, int_Y);
	float32 v2 = SmoothedNoise2D(int_X + 1, int_Y);
	float32 v3 = SmoothedNoise2D(int_X, int_Y + 1);
	float32 v4 = SmoothedNoise2D(int_X + 1, int_Y + 1);
	float32 i1 = Linear_Interpolate(v1, v2, fractional_X);
	float32 i2 = Linear_Interpolate(v3, v4, fractional_X);

	return Linear_Interpolate(i1, i2, fractional_Y);
}
float32 PerlinNoise2D(float32 x, float32 y, float32 factor)
{
	float32 total = 0;
	float32 frequency = 1.0f / std::pow(2.0f, frequencyStart);
	float32 persistence = 0.5f;
	float32 amplitude = 1.0f;
	x += factor;
	y += factor;
	for (int i = 0; i<octaves; ++i)
	{
		total += CompileNoise(x*frequency, y*frequency) * amplitude;
		amplitude *= persistence;
		frequency *= 2;
	}
	return total;
}



/*Функція генерації текстури*/
Texture*	texGenFunc()
{
	auto tex = new Texture;

	tex->Resize(uvec3(texSize, texSize, 1));

	srand(time(0));
	float32 factor = rand();

	for (uint32 x = 0; x < tex->GetSize().x; ++x)
	{
		for (uint32 y = 0; y < tex->GetSize().y; ++y)
		{
			vec4 color;

			{
				color.x = color.z = color.y = PerlinNoise2D((float32)x, (float32)y, factor);
				color.w = 1.0f;
				color.w = 1.0f;
			}

			tex->Get(x, y) = color;
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

	if (tTexture)
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

	if (tTexture)						// Виводимо текстуру
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

	if (tTexture)						// Очищаємо текстуру
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
	tWindow.SetSize(uvec2(texSize, texSize));
	tWindow.SetFunc(Window::Render::FuncTypes::Init, TexInitFunc);		// Встановлюємо функції ініціалізації
	tWindow.SetFunc(Window::Render::FuncTypes::Loop, TexRenderFunc);		// Рендеру (обробки)
	tWindow.SetFunc(Window::Render::FuncTypes::Free, TexFreeFunc);		// І звільнення ресурсів
	tWindow.SetRenderContext(Window::RenderContext::Types::OpenGL);		// Встановлюємо контекст рендеру

	while (Window::Process())
	{
		if (KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}












