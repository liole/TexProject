/*
�� ������� ����� �������, � ����� ������ �������� ��
����� ����, �������� ����(namespace) � ��������� �����������������
����� � ��������. ���� ����� ��������� � ����� ����� �� ��� ��������
����� �������, ��� ����������� 100% ������ �� ��� �������� � ������.
*/
#pragma once

/*
���������, �� ������������� �� ���������.
���� ���������� __TEXPROJECT_WIN__ - �� ����� �� Windows
__TEXPROJECT_LIN__ � __TEXPROJECT_MAC__ ������ �����������������
��� ���������� ����� �� Linux � MacOS ��������.
������ ��������� ��������� ���� ���� � ���.
*/
#define __TEXPROJECT_WIN__					1
//#define __TEXPROJECT_LIN__
//#define __TEXPROJECT_MAC__


/*
������ ����������� ��������� _DEBUG � ��������� ����� ������ -
������ ��������������� ������ ��������� __TEXPROJECT_DEBUG__
*/
#ifdef _DEBUG
#define __TEXPROJECT_DEBUG__
#endif


/*
� ����� ������ ������ ������ ���������-�������� ���.
*/
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


/*
ϳ�������� ���������-�������� ��������.
���� �� �� ������� ������� ��� ������ ����� ��� ��� �������,
���� �� ������� �� � �� ������ ���������� ������ ��� ��������
� �� ������ ����� ��� �� ���������.
*/
#include <string>
#include <HalfFloat/half.hpp>


namespace TexProject
{
	/*
	�� ���� ��������� ������ �������.
	�� �������, ����������, �����, ��������� � �.�., �� ����������
	������ ������� ��������� ���� � �����. ���������� ������ ����
	������� ������� �������, �� �� ���������������� �� ������
	�������� ������.
	*/
#ifdef __TEXPROJECT_WIN__

	/*
	���� void, bool � char ���� �� �������������.
	char ��������������� ���� ��� ������������� �������. ���
	������������� ����� � ����� ������ �����, ����� � �.�. ���������������
	������������ ���� int8/uint8.
	*/

	/*
	����� ���� ��� ������������� ����� �����
	*/
	// Integer
	/*8-���� ���� � ������*/
	typedef signed __int8					int8;
	/*8-���� ���� ��� �����*/
	typedef unsigned __int8					uint8;
	/*16-���� ���� � ������*/
	typedef signed __int16					int16;
	/*16-���� ���� ��� �����*/
	typedef unsigned __int16				uint16;
	/*32-���� ���� � ������*/
	typedef signed __int32					int32;
	/*32-���� ���� ��� �����*/
	typedef unsigned __int32				uint32;
	/*64-���� ���� � ������*/
	typedef signed __int64					int64;
	/*64-���� ���� ��� �����*/
	typedef unsigned __int64				uint64;

	/*
	����� ���� ��� ������������� ���������� � ��������� �����
	*/
	// Float
	/*16-���� ����� � ��������� �����*/
	typedef half_float::half				float16;
	/*32-���� ����� � ��������� �����*/
	typedef float							float32;
	/*64-���� ����� � ��������� �����*/
	typedef double							float64;

	/*
	����� ���� ��� ������ � �������
	*/
	// String
	/*����� char-�������*/
	typedef std::string						string;

	/*
	����� �������� ���� ��� ��������� ������ � ������� �������� �����,
	�� ���� ��������.
	*/

#else
#ifdef __TEXPROJECT_LIN__
	// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
	// MacOS variant
#endif
#endif
#endif

	/*
	���� ��� ������������� 2, 3 � 4-������������ ������� � �������,
	����������
	*/
	// Math
	/*2-������������ ������ float32*/
	struct									vec2;
	/*2-������������ ������ int32*/
	struct									ivec2;
	/*2-������������ ������ uint32*/
	struct									uvec2;
	/*3-������������ ������ float32*/
	struct									vec3;
	/*3-������������ ������ int32*/
	struct									ivec3;
	/*3-������������ ������ uint32*/
	struct									uvec3;
	/*4-������������ ������ float32*/
	struct									vec4;
	/*4-������������ ������ int32*/
	struct									ivec4;
	/*4-������������ ������ uint32*/
	struct									uvec4;
	/*������� 2�2 float32*/
	struct									mat2;
	/*������� 3�3 float32*/
	struct									mat3;
	/*������� 4�4 float32*/
	struct									mat4;
	/*��������� float32*/
	struct									quat;


	/*
	��������� ������� ����
	*/
	// Helpers
	namespace Helper
	{
		/*��������� ��������*/
		namespace Structure
		{
			/*
			���-���������, �� ������ ��������� �� �� ���������� �����.
			������� �������� � ��������� ���� ����������.
			*/
			template<typename T,bool autoAdd = false,bool autoRemove = true>
			struct IndirectClassArray;
		}
	}

	/*
	���� ��� ������ � ������.
	*/
	// Windows
	/*������� ������ ���� ��� ������ � ������*/
	namespace Window
	{
		struct Basic;
		struct Main;

		/*�����������*/
		void								Init();
		/*������������*/
		void								Free();
		/*������� ������� ��� ����.*/
		void								Process();
	}

}


















