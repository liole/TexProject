/*
�� ������ �������-����������, ��� ������ ������ ��
���� ��������. ��������� ���� ��������� ���� TexProject.h
� ����� ���������� ���� ��������� � ���������� TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;


void TexProject::Main()
{
	Window::Main a;
	Window::Render b;

	b.Create();
	b.SetRenderContext(Window::RenderContext::Types::OpenGL);

	a.Create();

	while(a.IsRunning() || b.IsRunning())
	{
		Window::Process();		

		if(KeyState(Keys::A)) a.Delete();
		if(KeyState(Keys::B)) b.Delete();
		if(KeyState(Keys::ESC)) break;
	}

	a.Delete();
	b.Delete();

}












