/*
В цьому модулі буде оголошена точка входу і різноманітні
базові функції.
*/
#pragma once
#include <TexProject/TexProject_Header.h>


#ifdef __TEXPROJECT_WIN__

#include <Windows.h>

#else
#ifdef __TEXPROJECT_LIN__
// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
// MacOS variant
#endif
#endif
#endif


namespace TexProject
{
	/*
	При написанні коду бажано вирівнювати початки назв функцій,
	для кращої читабельності. Я зазвичай вирівнюю по 25, 45, або 65 символах.
	При можливості коментуйте свої функції/класи так, як показано тут.
	Microsoft Visual Studio 2013 розпізнає такі коментарі і виводить їх
	як довідку при написанні функції.
	*/

	// Entry Point
	/*Структура для зберігання даних точки входу*/
	struct EntryPointData
	{
#ifdef __TEXPROJECT_WIN__
	public:

		static bool							init;
		static HINSTANCE					hInstance;
		static HINSTANCE					hPrevInstance;
		static LPSTR						lpCmdLine;
		static int							nShowCmd;

		EntryPointData() = delete;

#else
#ifdef __TEXPROJECT_LIN__
		// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
		// MacOS variant
#endif
#endif
#endif
	};

	/*
	Безпечний виклик точки входу.
	*/
	void				EntryPointSafeCall();
	/*
	Точка входу для кінцевого користувача.
	Цю функцію визначає користувач.
	*/
	void				Main();

	// Mesegges, Warnings, Errors
	/*
	Функції сповіщення і повідомлення про помилки.
	Викликати їх в Release збірці не рекомендовано, вони лише для своїх.
	*/


	/*
	Виводить повідомлення, не обов'язково про помилку.
	До натискання кнопки "ОК" не повертає контроль
	програмі(не виходить з функції).
	*/
	void				Message(const string& text);
	/*
	Виводить повідомлення про помилку і закриває програму
	після натискання кнопки "ОК".
	Використовувати при критичних помилках з неможливістю відновити
	правильне виконання програми.
	*/
	void				Error(const string& text);
	/*
	Виводить повідомлення з питанням і повертає true/false
	в залежності від того, натиснув користувач "Yes" чи "No".
	*/
	bool				Question(const string& text);


	/*Базовий клас для винятків*/
	struct Exception
	{
	public:
		string								text = "";

		inline								Exception() = default;
		inline								Exception(const string& text_);
		inline								Exception(const Exception& source) = default;
		//inline								Exception(Exception&& source) = delete;
		inline								~Exception() = default;

		inline Exception&					operator = (const Exception& source) = delete;
		//inline Exception&					operator = (Exception&& source) = delete;

		inline string						Get() const;
	};
	/*Помилка, що закриває програму*/
	struct ErrorException: public Exception
	{
		friend void TexProject::EntryPointSafeCall();
		friend void TexProject::Error(const string&);

		inline								ErrorException(const string& text_);

	private:
		inline static void					SecureCall(void(*func)(void));


		inline								ErrorException(const ErrorException& source) = default;
	};
}


// Exception
inline								TexProject::Exception::Exception(const string& text_):
	text(text_)
{
}
inline TexProject::string			TexProject::Exception::Get() const
{
	return text;
}


// ErrorException
inline void							TexProject::ErrorException::SecureCall(void(*func)(void))
{
	try
	{
		func();
	}
	catch(ErrorException exc)
	{
		MessageBox(0, exc.Get().c_str(), "[TexProject] Error", MB_OK);
		abort();
	}
}
inline								TexProject::ErrorException::ErrorException(const string& text_):
	Exception(text_)
{
}

















