#include <TexProject/TexProject.h>
using namespace TexProject;


Texture* tInputTexture = nullptr;		// ������ �������� �������
Texture* tOutputTexture = nullptr;		// ������� �������� �������


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
	Texture::InitDraw();	// ���������� ������� ��������� ��� ����� ����

	if(!tInputTexture)
	{
		tInputTexture = new Texture;
		tInputTexture->Load("Media/Images/3.PNG");	// ����������� ������ ��������
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
	if(KeyState(Keys::SPACE))				// ���� ���������� �������� �����
	{
		if(tOutputTexture)					// �������� ������� ��������
		{
			tOutputTexture->Draw();
		}
	}
	else
	{
		if(tInputTexture)					// �������� ������ ��������
		{
			tInputTexture->Draw();
		}
	}
}
void TexFreeFunc(Window::Render* window)
{
	if(tInputTexture)						// ������� ��������
	{
		delete tInputTexture;
		tInputTexture = nullptr;
	}
	if(tOutputTexture)						// ������� ��������
	{
		delete tOutputTexture;
		tOutputTexture = nullptr;
	}

	Texture::FreeDraw();				// ����������� ������� ���������
}


void TexProject::Main()
{
	Window::Render tWindow;

	tWindow.Create();
	tWindow.SetSize(uvec2(256,256));
	tWindow.SetFunc(Window::Render::FuncTypes::Init,TexInitFunc);		// ������������ ������� �����������
	tWindow.SetFunc(Window::Render::FuncTypes::Loop,TexRenderFunc);		// ������� (�������)
	tWindow.SetFunc(Window::Render::FuncTypes::Free,TexFreeFunc);		// � ��������� �������
	tWindow.SetRenderContext(Window::RenderContext::Types::OpenGL);		// ������������ �������� �������

	while(Window::Process())
	{
		if(KeyState(Keys::ESC)) break;
	}

	tWindow.Delete();
}












