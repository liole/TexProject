/*
�� ������ �������-����������, ��� ������ ������ ��
���� ��������. ��������� ���� ��������� ���� TexProject.h
� ����� ���������� ���� ��������� � ���������� TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;


void TexProject::Main()
{
	float16 hf;
	hf = 0.5;
	Message("Here we have a Message.\nHalfFloat value = "+std::to_string(hf));
	if( Question("And here we have a Question. Are we wanna Error?") )
	{
		Error("And here we have a Error!");
	}
}












