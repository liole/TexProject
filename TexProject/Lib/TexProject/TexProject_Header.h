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
#define __TEXPROJECT_PLATFORM_NONE__		0
#define __TEXPROJECT_PLATFORM_WIN__			1
#define __TEXPROJECT_PLATFORM_LIN__			2
#define __TEXPROJECT_PLATFORM_MAC__			3


#define __TEXPROJECT_PLATFORM__				__TEXPROJECT_PLATFORM_WIN__


#define __TEXPROJECT_ARCHITECTURE_UNKNOWN__	0
#define __TEXPROJECT_ARCHITECTURE_X64__		1
#define __TEXPROJECT_ARCHITECTURE_X86__		2


#define __TEXPROJECT_ARCHITECTURE__			__TEXPROJECT_ARCHITECTURE_X86__


#define __TEXPROJECT_WIN__					(__TEXPROJECT_PLATFORM__ == __TEXPROJECT_PLATFORM_WIN__)
#define __TEXPROJECT_LIN__					(__TEXPROJECT_PLATFORM__ == __TEXPROJECT_PLATFORM_LIN__)
#define __TEXPROJECT_MAC__					(__TEXPROJECT_PLATFORM__ == __TEXPROJECT_PLATFORM_MAC__)


#define __TEXPROJECT_MEMORY_LEAK__			0
#define __TEXPROJECT_OPENGL__				1
#define __TEXPROJECT_DEVIL__				1
#define __TEXPROJECT_DIRECT3D__				1


#define __TEXPROJECT_RTGSCRIPT__			0


/*
������ ����������� ��������� _DEBUG � ��������� ����� ������ -
������ ��������������� ������ ��������� __TEXPROJECT_DEBUG__
*/
#ifdef _DEBUG
#define __TEXPROJECT_DEBUG__				1
#endif


/*
� ����� ������ ������ ������ ���������-�������� ���.
*/
#if __TEXPROJECT_WIN__

#include <Windows.h>

#else
#if __TEXPROJECT_LIN__
// Linux variant
#else
#if __TEXPROJECT_MAC__
// MacOS variant
#endif
#endif
#endif



#if __TEXPROJECT_DEBUG__ && __TEXPROJECT_MEMORY_LEAK__
#include <VLD/include/vld.h>

#if __TEXPROJECT_ARCHITECTURE__ == __TEXPROJECT_ARCHITECTURE_X86__
#pragma comment(lib, "/Win32/vld.lib") 
#else
#pragma comment(lib, "/Win64/vld.lib") 
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
#if __TEXPROJECT_WIN__

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
#if __TEXPROJECT_LIN__
	// Linux variant
#else
#if __TEXPROJECT_MAC__
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


	// Main
	/*������� ���� ��� �������*/
	struct Exception;
	/*�������, �� ������� ��������*/
	struct ErrorException;


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
		struct Render;


		namespace RenderContext
		{

			/*������� �������� ������*/
			struct Basic;

#ifdef __TEXPROJECT_WIN__
			/*�������� Windows*/
			struct Default;
#endif

#ifdef __TEXPROJECT_OPENGL__
			/*�������� OpenGL*/
			struct OpenGL;
#endif

#ifdef __TEXPROJECT_DIRECT3D__
			/*�������� Direct3D*/
			struct Direct3D;
#endif
		
		};


		/*�����������*/
		void								Init();
		/*������������*/
		void								Free();
		/*������� ������� ��� ����.*/
		bool								Process();
	}


#if __TEXPROJECT_WIN__
	/*stuff fow windows*/
	namespace Windows
	{
		/*Windows textures(Bitmaps)*/
		struct Texture;
	}
#endif


#if __TEXPROJECT_OPENGL__
	/*��������� � ������ �������� OpenGL*/
	// OpenGL
	/*�������� ��������� OpenGL*/
	namespace OpenGL
	{
		// Shader
		/*���� �������*/
		struct Shader;

		namespace Buffer
		{
			//enum struct Type;

			namespace Attribute
			{
				//enum struct DataType;
				struct Params;
			}

			struct Data;
			struct Index;
			struct Array;
			struct Uniform;
			struct Transform;

			struct Frame;
		}

		struct Texture;
	}
#endif


#ifdef __TEXPROJECT_DIRECT3D__
	/*�������� ��������� Direct3D*/
	namespace Direct3D
	{
		namespace Buffer
		{
			struct Data;
			struct Index;
		}

		struct Shader;
	}
#endif


#if __TEXPROJECT_DEVIL__
	/*��������� � ������ �������� DevIL*/
	//DevIL
	/*�������� ��������� DevIL*/
	namespace DevIL
	{
	}
#endif


	// Textures
	/*��������� �������*/
	namespace Texture
	{
		struct D1;
		struct D2;
		struct D3;
		struct Cube;
	}


	//
	class	Lexer;
	class	Parser;
	struct	Checker;
	struct	Translator;
	struct	Script;
}


















