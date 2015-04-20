/*
�� ������ �������-����������, ��� ������ ������ ��
���� ��������. ��������� ���� ��������� ���� TexProject.h
� ����� ���������� ���� ��������� � ���������� TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;


void TexProject::Main()
{
	Window::Main a, b;
	a.Create();
	b.Create();

	while(a.IsRunning() || b.IsRunning())
	{
		Window::Process();		

		if(KeyState(Keys::A)) a.Delete();
		if(KeyState(Keys::B)) b.Delete();
	}

}












