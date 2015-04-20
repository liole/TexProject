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
}




















