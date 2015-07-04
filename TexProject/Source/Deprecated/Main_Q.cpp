#include <TexProject/TexProject.h>
using namespace TexProject;
using namespace TexProject::OpenGL;


Texture* tTexture = nullptr;


Texture* cellularTexGenFunc(uint32 dotNumber, uint32 width, uint32 height)
{
	auto tex = new Texture;
	tex->Resize(uvec3(width, height, 1));

	vec2* dotArr = new vec2[dotNumber];

	for (uint32 i = 0; i < dotNumber; ++i)
	{
		dotArr[i].x = rand() % width;
		dotArr[i].y = rand() % height;
	}


	vec4 color;
	for (uint32 x = 0; x < width; ++x)
	{
		for (uint32 y = 0; y < height; ++y)
		{
			float32 mindist = width*height;


			for (int i = 0; i < dotNumber; ++i)
			{
				float32 absx = fabs(float32(x) - dotArr[i].x);
				float32 absy = fabs(float32(y) - dotArr[i].y);
				if (absx > width / 2) absx = float32(width) - absx;
				if (absy > height / 2) absy = float32(height) - absy;
				float32 dist = sqrtf(absx*absx + absy*absy);
				if (dist < mindist) mindist = dist;
			}


			color.x = (1.0f - mindist / 100.0f)*0.45f;
			color.y = (1.0f - mindist / 100.0f)*0.88f;
			color.z = (1.0f - mindist / 100.0f)*0.50;
			color.w = (1.0f - mindist / 100.0f)*1.0f;

			tex->Get(x, y) = color;
		}
	}

	return tex;
}

void TexInitFunc(Window::Render* window)
{
	/*
	�� ������� ���� ��������� ������, �� ���� ���� ��������.
	window - �������� �� ����, ��� ������� �������.
	��� �� �������� ������� ��� �������� ������.
	*/

	Texture::InitDraw();	// ���������� ������� ��������� ��� ����� ����

	if (tTexture)
	{
		delete tTexture;
		tTexture = nullptr;
	}
	tTexture = cellularTexGenFunc(100, 128, 128);
	tTexture->Build(window);	
}
void TexRenderFunc(Window::Render* window)
{
	/*
	�� ������� ���� ����������� ��� ���� 60 ���� �� �������
	����, ���� ���� �� ��������.
	*/

	if (tTexture)						// �������� ��������
	{
		tTexture->Draw();
	}
}
void TexFreeFunc(Window::Render* window)
{
	/*
	�� ������� ����������� ����� ���������� ����.
	� �� �� ��������� �������.
	*/

	if (tTexture)						// ������� ��������
	{
		tTexture->Delete();
		tTexture = nullptr;
	}

	Texture::FreeDraw();				// ����������� ������� ���������
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.Create();
	tWindow.SetSize(uvec2(512, 512));
	tWindow.SetFunc(Window::Render::FuncTypes::Init, TexInitFunc);		// ������������ ������� �����������
	tWindow.SetFunc(Window::Render::FuncTypes::Loop, TexRenderFunc);		// ������� (�������)
	tWindow.SetFunc(Window::Render::FuncTypes::Free, TexFreeFunc);		// � ��������� �������
	tWindow.SetRenderContext(Window::RenderContext::Types::OpenGL);		// ������������ �������� �������

	while (Window::Process())
	{
		if (KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}

