/*
�� ������ �������-����������, ��� ������ ������ ��
���� ��������. ��������� ���� ��������� ���� TexProject.h
� ����� ���������� ���� ��������� � ���������� TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;
using namespace TexProject::OpenGL;


Texture* tTexture = nullptr;

/*������� ��������� ��������*/
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
	�� ������� ���� ��������� ������, �� ���� ���� ��������.
	window - �������� �� ����, ��� ������� �������.
	��� �� �������� ������� ��� �������� ������.
	*/

	Texture::InitDraw();	// ���������� ������� ��������� ��� ����� ����

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
	�� ������� ���� ����������� ��� ���� 60 ���� �� �������
	����, ���� ���� �� ��������.
	*/

	if(tTexture)						// �������� ��������
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

	if(tTexture)						// ������� ��������
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
	tWindow.SetSize(uvec2(512,512));
	tWindow.SetFunc(Window::Render::FuncTypes::Init,TexInitFunc);		// ������������ ������� �����������
	tWindow.SetFunc(Window::Render::FuncTypes::Render,TexRenderFunc);	// ������� (�������)
	tWindow.SetFunc(Window::Render::FuncTypes::Free,TexFreeFunc);		// � ��������� �������
	tWindow.SetRenderContext(Window::RenderContext::Types::OpenGL);		// ������������ �������� �������

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}












