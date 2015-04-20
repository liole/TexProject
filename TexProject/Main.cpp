/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
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












