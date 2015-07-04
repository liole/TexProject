/*
� ����� ����� ���� ��������� ����� ����� � ���������
����� �������.
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
	��� �������� ���� ������ ���������� ������� ���� �������,
	��� ����� ������������. � �������� ������� �� 25, 45, ��� 65 ��������.
	��� ��������� ���������� ��� �������/����� ���, �� �������� ���.
	Microsoft Visual Studio 2013 ������� ��� �������� � �������� ��
	�� ������ ��� �������� �������.
	*/

	// Entry Point
	/*��������� ��� ��������� ����� ����� �����*/
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
	��������� ������ ����� �����.
	*/
	void				EntryPointSafeCall();
	/*
	����� ����� ��� �������� �����������.
	�� ������� ������� ����������.
	*/
	void				Main();

	// Mesegges, Warnings, Errors
	/*
	������� ��������� � ����������� ��� �������.
	��������� �� � Release ����� �� �������������, ���� ���� ��� ����.
	*/


	/*
	�������� �����������, �� ����'������ ��� �������.
	�� ���������� ������ "��" �� ������� ��������
	�������(�� �������� � �������).
	*/
	void				Message(const string& text);
	/*
	�������� ����������� ��� ������� � ������� ��������
	���� ���������� ������ "��".
	��������������� ��� ��������� �������� � ����������� ��������
	��������� ��������� ��������.
	*/
	void				Error(const string& text);
	/*
	�������� ����������� � �������� � ������� true/false
	� ��������� �� ����, �������� ���������� "Yes" �� "No".
	*/
	bool				Question(const string& text);


	/*������� ���� ��� �������*/
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
	/*�������, �� ������� ��������*/
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

















