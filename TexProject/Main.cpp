/*
Це кінцева функція-користувач, яка отримує доступ до
нашої програми. Достатньо лише підключити файл TexProject.h
і увесь функціонал буде доступний з неймспейсу TexProject
*/
#include "Lib/TexProject/TexProject.h"
using namespace TexProject;


void TexProject::Main()
{
	Message("Here we have a Message.");
	if( Question("And here we have a Question. Are we wanna Error?") )
	{
		Error("And here we have a Error!");
	}
}












